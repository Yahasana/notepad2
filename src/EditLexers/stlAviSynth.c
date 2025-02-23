#include "EditLexer.h"
#include "EditStyleX.h"

static KEYWORDLIST Keywords_AVS = {{
//++Autogenerated -- start of section automatically generated
"__END__ __end__ bool catch clip else false float for func function global if int last no return string true try val "
"while yes "

, // 1 internal functions
"_Combed( _SceneChangeNext( _SceneChangePrev( "
"Abs( Acos( Apply( Asin( Assert( Atan( Atan2( AudioLengthHi( AudioLengthLo( "
"AverageB( AverageChromaU( AverageChromaV( AverageG( AverageLuma( AverageR( "
"BDifference( BDifferenceFromPrevious( BDifferenceToNext( BitAnd( BitChange( BitChg( BitClear( BitClr( "
"BitLRotate( BitLShift( BitNot( BitOr( BitRol( BitRor( BitRRotateL( BitRShiftA( BitRShiftL( BitRShiftS( BitRShiftU( "
"BitSal( BitSar( BitSet( BitSetCount( BitShl( BitShr( BitTest( BitTst( BitXor( "
"BPlaneMax( BPlaneMedian( BPlaneMin( BPlaneMinMaxDifference( BuildPixelType( "
"Ceil( Chr( ChromaUDifference( ChromaVDifference( "
"ColorSpaceNameToPixelType( ContinuedDenominator( ContinuedNumerator( Cos( Cosh( "
"Default( Defined( Eval( Exist( Exp( FillStr( FindStr( Float( Floor( Fmod( Format( Frac( FunctionExists( "
"GDifference( GDifferenceFromPrevious( GDifferenceToNext( GetParity( GetProcessInfo( GEval( GImport( "
"GPlaneMax( GPlaneMedian( GPlaneMin( GPlaneMinMaxDifference( GScript( "
"Hex( HexValue( Import( Int( InternalFunctionExists( IsBool( IsClip( IsFloat( IsInt( IsString( IsVersionOrGreater( "
"LCase( LeftStr( "
"Load_Stdcall_Plugin( LoadCPlugin( LoadPlugin( LoadVFAPIPlugin( LoadVirtualDubPlugin( Log( Log10( LogMsg( "
"LumaDifference( "
"Max( MidStr( Min( MulDiv( NOP( Ord( "
"Pi( Pow( propDelete( "
"propGetAny( propGetAsArray( propGetDataSize( propGetFloat( propGetInt( propGetKeyByIndex( propGetString( propGetType( "
"propNumElements( propNumKeys( propSet( propSetArray( propSetFloat( propSetInt( propSetString( propShow( "
"Rand( RDifference( RDifferenceFromPrevious( RDifferenceToNext( ReplaceStr( RevStr( "
"RGBDifference( RGBDifferenceFromPrevious( RGBDifferenceToNext( RightStr( Round( "
"RPlaneMax( RPlaneMedian( RPlaneMin( RPlaneMinMaxDifference( "
"ScriptDir( ScriptDirUtf8( ScriptFile( ScriptFileUtf8( ScriptName( ScriptNameUtf8( "
"Select( SetCacheMode( SetLogParams( SetMaxCPU( SetMemoryMax( SetPlanarLegacyAlignment( SetWorkingDir( Sign( Sin( Sinh( "
"Spline( Sqrt( StrCmp( StrCmpi( StrFromUtf8( String( StrLen( StrToUtf8( "
"Tan( Tanh( Time( TrimAll( TrimLeft( TrimRight( "
"UCase( UDifferenceFromPrevious( UDifferenceToNext( Undefined( "
"UPlaneMax( UPlaneMedian( UPlaneMin( UPlaneMinMaxDifference( "
"Value( VarExist( VDifferenceFromPrevious( VDifferenceToNext( VersionNumber( VersionString( "
"VPlaneMax( VPlaneMedian( VPlaneMin( VPlaneMinMaxDifference( "
"YDifferenceFromPrevious( YDifferenceToNext( YPlaneMax( YPlaneMedian( YPlaneMin( YPlaneMinMaxDifference( "

, // 2 internal filters
"AddBorders( AlignedSplice( Amplify( AmplifyDB( Animate( ApplyRange( "
"AssumeBFF( AssumeFieldBased( AssumeFPS( AssumeFrameBased( AssumeSampleRate( AssumeScaledFPS( AssumeTFF( "
"AudioDub( AudioDubEx( AudioTrim( AviFileSource( AviSource( "
"BicubicResize( BilinearResize( BlackmanResize( Blackness( BlankClip( Blur( Bob( "
"ChangeFPS( ColorBars( ColorBarsHD( ColorKeyMask( ColorYUV( Compare( ComplementParity( "
"ConditionalFilter( ConditionalReader( ConditionalSelect( "
"ConvertAudioTo16bit( ConvertAudioTo24bit( ConvertAudioTo32bit( ConvertAudioTo8bit( ConvertAudioToFloat( "
"ConvertBackToYUY2( ConvertFPS( ConvertToMono( ConvertToPlanarRGB( ConvertToPlanarRGBA( "
"ConvertToRGB( ConvertToRGB24( ConvertToRGB32( ConvertToRGB48( ConvertToRGB64( ConvertToY( ConvertToY8( "
"ConvertToYUV420( ConvertToYUV422( ConvertToYUV444( ConvertToYUY2( "
"ConvertToYV12( ConvertToYV16( ConvertToYV24( ConvertToYV411( Crop( CropBottom( "
"DelayAudio( DeleteFrame( DirectShowSource( Dissolve( DoubleWeave( DuplicateFrame( Echo( EnsureVBRMP3Sync( "
"FadeIn( FadeIn0( FadeIn2( FadeIO( FadeIO0( FadeIO2( FadeOut( FadeOut0( FadeOut2( "
"FixBrokenChromaUpsampling( FixLuminance( FlipHorizontal( FlipVertical( FrameEvaluate( FreezeFrame( "
"GaussResize( GeneralConvolution( GetChannel( GetChannels( GetLeftChannel( GetRightChannel( Grayscale( Greyscale( "
"Histogram( HorizontalReduceBy2( ImageReader( ImageSource( ImageSourceAnim( ImageWriter( Info( Interleave( Invert( "
"KillAudio( KillVideo( Lanczos4Resize( LanczosResize( Layer( Letterbox( Levels( Limiter( Loop( "
"Mask( MaskHS( Merge( MergeARGB( MergeChannels( MergeChroma( MergeLuma( MergeRGB( MessageClip( MixAudio( MonoToStereo( "
"Normalize( OpenDMLSource( Overlay( PeculiarBlend( PointResize( Preroll( Pulldown( "
"ReduceBy2( ResampleAudio( ResetMask( Reverse( RGBAdjust( "
"ScriptClip( SegmentedAviSource( SegmentedDirectShowSource( SelectEven( SelectEvery( SelectOdd( SelectRangeEvery( "
"SeparateColumns( SeparateFields( SeparateRows( "
"Sharpen( ShowAlpha( ShowBlue( ShowFiveVersions( ShowFrameNumber( ShowGreen( ShowRed( ShowSMPTE( ShowTime( SincResize( "
"SkewRows( SpatialSoften( Spline16Resize( Spline36Resize( Spline64Resize( SSRC( StackHorizontal( StackVertical( "
"Subtitle( Subtract( SuperEQ( SwapFields( SwapUV( "
"TCPServer( TCPSource( TemporalSoften( TimeStretch( Tone( Trim( Turn180( TurnLeft( TurnRight( Tweak( "
"UnalignedSplice( UToY( UToY8( Version( VerticalReduceBy2( VToY( VToY8( "
"WavSource( Weave( WeaveColumns( WeaveRows( WriteFile( WriteFileEnd( WriteFileIf( WriteFileStart( YToUV( "

, // 3 external filters
"_2DCleanYUY2( "
"abcxyz( AdaptiveMedian( AddAudio( AddGrain( AddGrainC( AddlogoHD( AnalyzeLogo( Anime4KCPP( AnimeIVTC( "
"ApparentFPS( ApplyEvery( ApplyGradationCurves( ApplyInterlacedFilter( AreaResize( "
"ASharp( aSobel( AssRender( ASTDR( ASTDRmc( AudioGraph( AudioMax( AudioMin( AudioRMS( AudioTimeline( AutoCrop( "
"Average( AverageBlur( AvsMotion( aWarpSharpDering( "
"BackwardClense( Barrel( Befa( BestAudioSource( Bifrost( BinomialBlur( BlindDeHalo3( BorderControl( "
"BucketMedian( Butteraugli( BWDIF( "
"CacheAudio( caf( CallCmd( CAS( cc( Cdeblend( Cdeint( "
"ChanMix( ChannelMixer( Checkmate( ChromaShift( ChromaShiftSP( ChubbyRain( ChubbyRain2( "
"cl_expr( cl_exprxy( cl_exprxyz( Clense( ClipBlend( ClipBlend16( ClipClop( Cnr2( "
"ColorBalance( ColorDiff( Colorize( ColorMatrix( ColorRangeMask( ColourMask( ColourStabilise( ColourWarp( "
"CombMask( CombMask2( ConditionalFilterMT( ContinuityFixer( ContinuousMask( "
"Convert60ito24p( ConvertFpsLimit( ConvertFromShader( ConvertToShader( CoronaSequence( Cube( "
"DCTFilter( DCTFilter4( DCTFilter4D( DCTFilter8( DCTFilter8D( DCTFilterD( DCTFun4b( DCTFun4c( DCTFun5( Deathray( "
"Debicubic( DebicubicY( Debilinear( DebilinearY( DeBlend( DeblendLogo( Deblock( DeBlock_QED( DeblockPP7( "
"DecombUCF( DeCrawl( DeCross( DeDot( Deen( Defish( Deflicker( DeGrainMedian( DeHalo_alpha( DeHaloHmod( "
"DeleteEvery( DeleteFrames( DelogoHD( DeNoise( Depansafe( DePulse( DeRainbow( DeRainbowYUY2( "
"DeSaltPepper( descratch( Deshaker3D( Deskew( DeSpot( deVCR( DFMDeRainbow( dftTest( "
"DGHable( DGHDRtoSDR( DGPQtoHLG( DGReinhard( DistanceFunction( DSS2( DumpPixelValues( Dup1( DupStep( "
"EdgeCleaner( EEDI2( EffectsMany( EquLines( "
"ExactDedup( Exblend( ExecuteShader( ExInpaint( ExpotencialLimiter( ExtendedBilateral( "
"F1Quiver( F3kGrain( FastBlur( FCBI( FDecimate( FDecimate2( "
"ffdshow( ffdshowAudio( FFmpegSource2( FFT3DFilter( FFT3DGPU( FFTSpectrum( FieldHint( "
"FileSize( FillBorders( FillMargins( FineDehalo( FineSharp( Fingerprint( "
"FixBlendIVTC( FixChromaBleeding( FixChromaBleedingMod( FixChromaticAberration( FixFPS( FluxSmoothST( FluxSmoothT( "
"ForwardClense( FrameDbl( FrameRateConverter( FrameRepeat( FrameSel( FreeSub( FrFun3b( FrFun3d( FrFun7( FunkyDeBlock( "
"GaussianBlur( GBlur( GetMTMode( GetProgramName2( Ghostbuster( GiCoCu( GNoise( "
"GradFun2DB( GradFun2DBmod( GrainFactory3( GraMaMa( Grid( "
"HDRAGC( HistogramCMYLevels( HistogramRGBLevels( HQDering( HQDeringmod( HQdn3d( HShear( HSIAdjust( HSLAdjust( HSVAdjust( "
"Hue( Hysteria( "
"Info2( InpaintAssist( InpaintFunc( InpaintLogo( "
"InterlacedResize( InterlacedWarpedResize( InterleaveEvery( InterpolateDoubles( IsCombed2( IsHinted( IT( ivtc_txt60mc( "
"Jinc144Resize( Jinc256Resize( Jinc36Resize( Jinc64Resize( JincResize( JpegSource( KillHints( KillPulse( KNLMeansCL( "
"LazyDering( LeakKernelBob( LeakKernelDeint( LengthenClip( LGhost( LimitedSharpenFaster( LinearLimiter( listGPUs( "
"LoadDLL( LSFmod( LumaYV12( LUTDeCrawl( LUTDeRainbow( "
"maa2( MaskedMerge2( MaskSub( MaskSubMod( MatchHistogram( MaxCLLFind( MC_Spuds( MCTemporalDenoise( MDeblock( MDEC2( "
"Median( MedianBlur( MedianBlurTemporal( mfRainbow( mfToon2( mfToonLite( MiniDeen( MosquitoNR( MoveChroma( "
"MPEG2Source( MPlayerNoise( mrestore( MSCDetection( MSharpen( MT( mt_edge( mt_YRangeMask( MTi( MTsource( "
"neo_vd( NicAC3Source( NicDTSSource( NicLPCMSource( NicMPG123Source( nnedi3( nnedi3_rpow2( nnedi3ocl( "
"NoiseGenerator( NonlinUSM( Normalize2( "
"OutRange( OverlayCompare( OverlayConfig( OverlayEngine( OverlayRender( "
"PackedToPlanar( PixelScope( PlanarToRGB32( Posterize( proToon( Prune( pSharpen( QTInput( "
"Rainbow_Smooth( RAverageM( RAverageW( RaWavSource( RawSequence( RawSource( ReCon( ReduceFlicker( ReferenceFixerFixer( "
"ReInterpolate411( RemapFrames( RemapFramesSimple( removeblend( RemoveGrain( "
"Repair( RepeatEveryFrame( ReplaceFramesSimple( Resize8( RestoreFPS( RestoreMotionBlocks( RGBColourStabilise( RGBToRGB( "
"rm_logo( RMerge( RoboCrop( Rotate( "
"salFPS3( SangNom2( santiag( Scanlines( scharr( SCXvid( SCXvidMask( "
"SeeSaw( SegmentedAmp( SelectiveColour( Sepia( SetMTmode( Shader( ShowOverRange( ShowPixelValues( "
"SickJumps( SimpleResize( Skew( SmartSSIQ( SmoothD( SmoothD2( SmoothUV( SoftLight( Soothe( SoxFilter( "
"SpecificEffectName( Spectrogram( SPresso( srestore( "
"SSHiQ( SSIM( SSIM_FRAME( SSIM_U_FRAME( SSIM_V_FRAME( SSIM_Y_FRAME( SSIQ( SSSharp( "
"Stab( StaticNoiseC( STMedianFilter( STPresso( StripeMask( SubtitleEx( SuperToon( SupTitle( "
"TBilateral( tcanny( TCannyMod( TColorMask( TComb( TCombMask( TDeint( Technicolor( TEdgeMask( TelecideHints( "
"TEMmod( TempGaussMC_beta2( TempLinearApproximate( TemporalDegrain( TemporalRepair( "
"TextSub( TextSubMod( TextSubModSwapUV( TextSubSwapUV( TimecodeFPS( TIsophote( TMaskCleaner( TMM( TMM2( TNLMeans( "
"Toon( ToonLite( Transition( TTempSmooth( TTempSmoothF( TUnsharp( TurnsTile( TweakColor( TweakHist( "
"UnDot( UnFilter( Unpremultiply( Unsharp( UnsharpHQ( uu_mt_blend( "
"VagueDenoiser( VerticalCleaner( VFRtoCFR( VideoScope( ViewAudio( Vinverse( Vinverse2( VMAF( vmToon( VobSub( "
"vsDeblockPP7( VSEval( VShear( VSImport( vsMSharpen( vsMSmooth( vsTTempSmooth( "
"WarpedResize( Watermark2( Waveform( WavGainLimiter( WhileEval( WhiteBalance( xaa( "
"Yadif( yadifmod( yadifmod2( YAHR( YARK( YFRC( YV12To422( "
"z_BicubicResize( z_BilinearResize( z_ConvertFormat( z_Lanczos4Resize( z_LanczosResize( z_PointResize( "
"z_Spline16Resize( z_Spline36Resize( z_Spline64Resize( Zoom( "

, // 4 properties
"_AbsoluteTime _ChromaLocation _ColorRange _DurationDen _DurationNum _Field _FieldBased _Matrix _PictType _Primaries "
"_SARDen _SARNum _Transfer "
"AudioBits AudioChannels AudioDuration AudioLength AudioLengthF AudioLengthS AudioRate BitsPerComponent ComponentSize "
"FrameCount FrameRate FrameRateDenominator FrameRateNumerator HasAlpha HasAudio HasVideo Height "
"Is420 Is422 Is444 IsAudioFloat IsAudioInt IsFieldBased IsFrameBased IsInterleaved "
"IsPackedRGB IsPlanar IsPlanarRGB IsPlanarRGBA IsRGB IsRGB24 IsRGB32 IsRGB48 IsRGB64 "
"IsY IsY8 IsYUV IsYUVA IsYUY2 IsYV12 IsYV16 IsYV24 IsYV411 "
"NumComponents PixelType Width "

, // 5 options
"OPT_AVIPadScanlines OPT_AllowFloatAudio "
"OPT_Enable_PlanarToPackedRGB OPT_Enable_V210 OPT_Enable_Y3_10_10 OPT_Enable_Y3_10_16 OPT_Enable_b64a "
"OPT_UseWaveExtensible OPT_VDubPlanarHack OPT_dwChannelMask( "

, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
//--Autogenerated -- end of section automatically generated
}};

static EDITSTYLE Styles_AVS[] = {
	EDITSTYLE_DEFAULT,
	{ SCE_AVS_KEYWORD, NP2StyleX_Keyword, L"bold; fore:#FF8000" },
	{ SCE_AVS_FUNCTION, NP2StyleX_BuiltInFunction, L"fore:#0080C0" },
	{ SCE_AVS_FILTER, NP2StyleX_InternalFilter, L"fore:#648000" },
	{ SCE_AVS_PLUGIN, NP2StyleX_ExternalFilter, L"fore:#7C5AF3" },
	{ SCE_AVS_CLIPPROP, NP2StyleX_Property, L"fore:#007F7F" },
	{ SCE_AVS_USERDFN, NP2StyleX_Function, L"fore:#A46000" },
	{ MULTI_STYLE(SCE_AVS_COMMENTLINE, SCE_AVS_COMMENTBLOCK, SCE_AVS_COMMENTBLOCKN, 0), NP2StyleX_Comment, L"fore:#608060" },
	{ SCE_AVS_TASKMARKER, NP2StyleX_TaskMarker, L"bold; fore:#408080" },
	{ MULTI_STYLE(SCE_AVS_STRING, SCE_AVS_ESCAPESTRING, 0, 0), NP2StyleX_String, L"fore:#008000" },
	{ SCE_AVS_TRIPLESTRING, NP2StyleX_TripleQuotedString, L"fore:#F08000" },
	{ SCE_AVS_ESCAPECHAR, NP2StyleX_EscapeSequence, L"fore:#0080C0" },
	{ SCE_AVS_NUMBER, NP2StyleX_Number, L"fore:#FF0000" },
	{ SCE_AVS_OPERATOR, NP2StyleX_Operator, L"fore:#B000B0" },
};

EDITLEXER lexAviSynth = {
	SCLEX_AVISYNTH, NP2LEX_AVISYNTH,
//Settings++Autogenerated -- start of section automatically generated
	{
		LexerAttr_Default,
		TAB_WIDTH_4, INDENT_WIDTH_4,
		(1 << 0), // function
		0,
		'\\', SCE_AVS_ESCAPECHAR, 0,
		0,
		0, 0,
		SCE_AVS_OPERATOR, 0
		, KeywordAttr32(0, KeywordAttr_PreSorted) // keywords
		| KeywordAttr32(1, KeywordAttr_MakeLower | KeywordAttr_PreSorted) // internal functions
		| KeywordAttr32(2, KeywordAttr_MakeLower | KeywordAttr_PreSorted) // internal filters
		| KeywordAttr32(3, KeywordAttr_MakeLower | KeywordAttr_PreSorted) // external filters
		| KeywordAttr32(4, KeywordAttr_MakeLower | KeywordAttr_PreSorted) // properties
		| KeywordAttr32(5, KeywordAttr_NoLexer) // options
	},
//Settings--Autogenerated -- end of section automatically generated
	EDITLEXER_HOLE(L"AviSynth Script", Styles_AVS),
	L"avs; avsi",
	&Keywords_AVS,
	Styles_AVS
};
