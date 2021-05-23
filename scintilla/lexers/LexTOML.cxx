// This file is part of Notepad2.
// See License.txt for details about distribution and modification.
//! Lexer for TOML.

#include <cassert>
#include <cstring>

#include "ILexer.h"
#include "Scintilla.h"
#include "SciLexer.h"

#include "WordList.h"
#include "LexAccessor.h"
#include "Accessor.h"
#include "StyleContext.h"
#include "CharacterSet.h"
#include "LexerModule.h"

using namespace Lexilla;

namespace {

struct EscapeSequence {
	int outerState = SCE_TOML_DEFAULT;
	int digitsLeft = 0;

	// highlight any character as escape sequence.
	void resetEscapeState(int state, int chNext) noexcept {
		outerState = state;
		digitsLeft = 1;
		if (chNext == 'x') {
			digitsLeft = 3;
		} else if (chNext == 'u') {
			digitsLeft = 5;
		} else if (chNext == 'U') {
			digitsLeft = 9;
		}
	}
	bool atEscapeEnd(int ch) noexcept {
		--digitsLeft;
		return digitsLeft <= 0 || !IsHexDigit(ch);
	}
};

constexpr bool IsTOMLOperator(int ch) noexcept {
	return AnyOf(ch, '[', ']', '{', '}', ',', '=', '.', '+', '-');
}

constexpr bool IsTOMLDateTime(int ch, int chNext) noexcept {
	return ((ch == '-' || ch == ':' || ch == '.') && IsADigit(chNext))
		|| (ch == ' ' && (chNext == '-' || IsADigit(chNext)));
}

constexpr bool IsTOMLUnquotedKey(int ch) noexcept {
	return IsIdentifierChar(ch) || ch == '-';
}

bool IsTOMLKey(StyleContext& sc, int braceCount, const WordList *kwList) {
	if (braceCount) {
		const int chNext = sc.GetDocNextChar();
		if (chNext == '=' || chNext == '.' || chNext == '-') {
			sc.ChangeState(SCE_TOML_KEY);
			return true;
		}
	}
	if (sc.state == SCE_TOML_IDENTIFIER) {
		char s[8];
		sc.GetCurrentLowered(s, sizeof(s));
		if (kwList->InList(s)) {
			sc.ChangeState(SCE_TOML_KEYWORD);
		}
	}
	sc.SetState(SCE_TOML_DEFAULT);
	return false;
}

enum {
	TOMLLineType_None = 0,
	TOMLLineType_Table = 1,
	TOMLLineType_CommentLine = 2,

	TOMLKeyState_Unquoted = 0,
	TOMLKeyState_Literal = 1,
	TOMLKeyState_Quoted = 2,
	TOMLKeyState_End = 3,
};

void ColouriseTOMLDoc(Sci_PositionU startPos, Sci_Position lengthDoc, int initStyle, LexerWordList keywordLists, Accessor &styler) {
	int visibleChars = 0;
	int tableLevel = 0;
	int braceCount = 0;
	int lineType = TOMLLineType_None;
	int keyState = TOMLKeyState_Unquoted;
	EscapeSequence escSeq;

	StyleContext sc(startPos, lengthDoc, initStyle, styler);
	if (sc.currentLine > 0) {
		const int lineState = styler.GetLineState(sc.currentLine - 1);
		/*
		2: lineType
		8: tableLevel
		8: braceCount
		*/
		braceCount = (lineState >> 10) & 0xff;
	}

	while (sc.More()) {
		switch (sc.state) {
		case SCE_TOML_OPERATOR:
			sc.SetState(SCE_TOML_DEFAULT);
			break;

		case SCE_TOML_NUMBER:
			if (!IsDecimalNumber(sc.chPrev, sc.ch, sc.chNext)) {
				if (IsTOMLDateTime(sc.ch, sc.chNext)) {
					sc.ChangeState(SCE_TOML_DATETIME);
				} else if (IsTOMLKey(sc, braceCount, nullptr)) {
					continue;
				}
			}
			break;

		case SCE_TOML_DATETIME:
			if (!(IsIdentifierChar(sc.ch) || IsTOMLDateTime(sc.ch, sc.chNext))) {
				if (IsTOMLKey(sc, braceCount, nullptr)) {
					continue;
				}
			}
			break;

		case SCE_TOML_IDENTIFIER:
			if (!IsIdentifierChar(sc.ch)) {
				if (IsTOMLKey(sc, braceCount, keywordLists[0])) {
					continue;
				}
			}
			break;

		case SCE_TOML_TABLE:
		case SCE_TOML_KEY:
			if (sc.atLineStart) {
				sc.SetState(SCE_TOML_DEFAULT);
			} else {
				switch (keyState) {
				case TOMLKeyState_Literal:
					if (sc.ch == '\'') {
						sc.Forward();
						keyState = TOMLKeyState_Unquoted;
					}
					break;
				case TOMLKeyState_Quoted:
					if (sc.ch == '\\') {
						sc.Forward();
					} else if (sc.ch == '\"') {
						sc.Forward();
						keyState = TOMLKeyState_Unquoted;
					}
					break;
				default:
					break;
				}
				if (keyState == TOMLKeyState_Unquoted) {
					if (sc.ch == '\'') {
						keyState = TOMLKeyState_Literal;
					} else if (sc.ch == '\"') {
						keyState = TOMLKeyState_Quoted;
					} else if (sc.ch == '.') {
						if (sc.state == SCE_TOML_KEY) {
							sc.SetState(SCE_TOML_OPERATOR);
							sc.ForwardSetState(SCE_TOML_KEY);
						} else {
							++tableLevel;
						}
					} else if (sc.state == SCE_TOML_KEY && sc.ch == '=') {
						sc.SetState(SCE_TOML_OPERATOR);
					} else if (sc.state == SCE_TOML_TABLE && sc.ch == ']') {
						keyState = TOMLKeyState_End;
						sc.Forward();
						if (sc.ch == ']') {
							sc.Forward();
						}
						const int chNext = sc.GetLineNextChar();
						if (chNext == '#') {
							sc.SetState(SCE_TOML_DEFAULT);
						}
					}
				}
			}
			break;

		case SCE_TOML_STRING_SQ:
			if (sc.atLineStart) {
				sc.SetState(SCE_TOML_DEFAULT);
			} else if (sc.ch == '\'') {
				sc.Forward();
				if (IsTOMLKey(sc, braceCount, nullptr)) {
					continue;
				}
				sc.SetState(SCE_TOML_DEFAULT);
			}
			break;

		case SCE_TOML_STRING_DQ:
			if (sc.atLineStart) {
				sc.SetState(SCE_TOML_DEFAULT);
			} else if (sc.ch == '\\') {
				escSeq.resetEscapeState(sc.state, sc.chNext);
				sc.SetState(SCE_TOML_ESCAPECHAR);
				sc.Forward();
			} else if (sc.ch == '\"') {
				sc.Forward();
				if (IsTOMLKey(sc, braceCount, nullptr)) {
					continue;
				}
				sc.SetState(SCE_TOML_DEFAULT);
			}
			break;

		case SCE_TOML_TRIPLE_STRING_SQ:
			if (sc.Match('\'', '\'', '\'')) {
				sc.Forward(2);
				sc.ForwardSetState(SCE_TOML_DEFAULT);
			}
			break;

		case SCE_TOML_TRIPLE_STRING_DQ:
			if (sc.ch == '\\') {
				escSeq.resetEscapeState(sc.state, sc.chNext);
				sc.SetState(SCE_TOML_ESCAPECHAR);
				sc.Forward();
			} else if (sc.Match('"', '"', '"')) {
				sc.Forward(2);
				sc.ForwardSetState(SCE_TOML_DEFAULT);
			}
			break;

		case SCE_TOML_ESCAPECHAR:
			if (escSeq.atEscapeEnd(sc.ch)) {
				sc.SetState(escSeq.outerState);
				continue;
			}
			break;

		case SCE_TOML_COMMENT:
		case SCE_TOML_ERROR:
			if (sc.atLineStart) {
				sc.SetState(SCE_TOML_DEFAULT);
			}
			break;
		}

		if (sc.state == SCE_TOML_DEFAULT) {
			if (visibleChars == 0 && !braceCount) {
				if (sc.ch == '#') {
					sc.SetState(SCE_TOML_COMMENT);
					lineType = TOMLLineType_CommentLine;
				} else if (sc.ch == '[') {
					tableLevel = 0;
					sc.SetState(SCE_TOML_TABLE);
					if (sc.chNext == '[') {
						sc.Forward();
					}
					keyState = TOMLKeyState_Unquoted;
					lineType = TOMLLineType_Table;
				} else if (sc.ch == '\'' || sc.ch == '\"') {
					sc.SetState(SCE_TOML_KEY);
					keyState = (sc.ch == '\'')? TOMLKeyState_Literal : TOMLKeyState_Quoted;
				} else if (IsTOMLUnquotedKey(sc.ch)) {
					sc.SetState(SCE_TOML_KEY);
					keyState = TOMLKeyState_Unquoted;
				} else if (!isspacechar(sc.ch)) {
					// each line must be: key = value
					sc.SetState(SCE_TOML_ERROR);
				}
			} else {
				if (sc.ch == '#') {
					sc.SetState(SCE_TOML_COMMENT);
					if (visibleChars == 0) {
						lineType = TOMLLineType_CommentLine;
					}
				} else if (sc.ch == '\'') {
					if (sc.MatchNext('\'', '\'')) {
						sc.SetState(SCE_TOML_TRIPLE_STRING_SQ);
						sc.Forward(2);
					} else {
						sc.SetState(SCE_TOML_STRING_SQ);
					}
				} else if (sc.ch == '"') {
					if (sc.MatchNext('"', '"')) {
						sc.SetState(SCE_TOML_TRIPLE_STRING_DQ);
						sc.Forward(2);
					} else {
						sc.SetState(SCE_TOML_STRING_DQ);
					}
				} else if (IsADigit(sc.ch)) {
					sc.SetState(SCE_TOML_NUMBER);
				} else if (IsLowerCase(sc.ch)) {
					sc.SetState(SCE_TOML_IDENTIFIER);
				} else if (IsTOMLOperator(sc.ch)) {
					sc.SetState(SCE_TOML_OPERATOR);
					if (sc.ch == '[' || sc.ch == '{') {
						++braceCount;
					} else if (sc.ch == ']' || sc.ch == '}') {
						--braceCount;
					}
				} else if (braceCount && IsTOMLUnquotedKey(sc.ch)) {
					// Inline Table
					sc.SetState(SCE_TOML_KEY);
					keyState = TOMLKeyState_Unquoted;
				}
			}
		}

		if (visibleChars == 0 && !isspacechar(sc.ch)) {
			++visibleChars;
		}
		if (sc.atLineEnd) {
			const int lineState = (tableLevel << 2) | (braceCount << 10) | lineType;
			styler.SetLineState(sc.currentLine, lineState);
			lineType = TOMLLineType_None;
			visibleChars = 0;
			tableLevel = 0;
			keyState = TOMLKeyState_Unquoted;
		}
		sc.Forward();
	}

	sc.Complete();
}

constexpr int GetLineType(int lineState) noexcept {
	return lineState & 3;
}

constexpr int GetTableLevel(int lineState) noexcept {
	return (lineState >> 2) & 0xff;
}

// code folding based on LexProps
void FoldTOMLDoc(Sci_PositionU startPos, Sci_Position lengthDoc, int /*initStyle*/, LexerWordList, Accessor &styler) {
	const Sci_Line endPos = startPos + lengthDoc;
	const Sci_Line maxLines = styler.GetLine((endPos == styler.Length()) ? endPos : endPos - 1);

	Sci_Line lineCurrent = styler.GetLine(startPos);

	int prevLevel = SC_FOLDLEVELBASE;
	bool prevComment = false;
	bool prev2Comment = false;
	if (lineCurrent > 0) {
		prevLevel = styler.LevelAt(lineCurrent - 1);
		prevComment = GetLineType(styler.GetLineState(lineCurrent - 1)) == TOMLLineType_CommentLine;
		prev2Comment = lineCurrent > 1 && GetLineType(styler.GetLineState(lineCurrent - 2)) == TOMLLineType_CommentLine;
	}

	bool commentHead = prevComment && (prevLevel & SC_FOLDLEVELHEADERFLAG);
	while (lineCurrent <= maxLines) {
		int nextLevel;
		const int lineState = styler.GetLineState(lineCurrent);
		const int lineType = GetLineType(lineState);

		const bool currentComment = lineType == TOMLLineType_CommentLine;
		if (currentComment) {
			commentHead = !prevComment;
			if (prevLevel & SC_FOLDLEVELHEADERFLAG) {
				nextLevel = (prevLevel & SC_FOLDLEVELNUMBERMASK) + 1;
			} else {
				nextLevel = prevLevel;
			}
			nextLevel |= commentHead ? SC_FOLDLEVELHEADERFLAG : 0;
		} else {
			if (lineType == TOMLLineType_Table) {
				nextLevel = SC_FOLDLEVELBASE + GetTableLevel(lineState);
				if (prevComment && prevLevel <= nextLevel) {
					// comment above nested table
					commentHead = false;
					styler.SetLevel(lineCurrent - 1, prevLevel - 1);
				}
				nextLevel |= SC_FOLDLEVELHEADERFLAG;
			} else {
				if (commentHead) {
					nextLevel = prevLevel & SC_FOLDLEVELNUMBERMASK;
				} else if (prevLevel & SC_FOLDLEVELHEADERFLAG) {
					nextLevel = (prevLevel & SC_FOLDLEVELNUMBERMASK) + 1;
				} else if (prevComment && prev2Comment) {
					nextLevel = prevLevel - 1;
				} else {
					nextLevel = prevLevel;
				}
			}

			if (commentHead) {
				commentHead = false;
				styler.SetLevel(lineCurrent - 1, prevLevel & SC_FOLDLEVELNUMBERMASK);
			}
		}

		if (nextLevel != styler.LevelAt(lineCurrent)) {
			styler.SetLevel(lineCurrent, nextLevel);
		}

		prevLevel = nextLevel;
		prev2Comment = prevComment;
		prevComment = currentComment;
		lineCurrent++;
	}
}

}

LexerModule lmTOML(SCLEX_TOML, ColouriseTOMLDoc, "toml", FoldTOMLDoc);
