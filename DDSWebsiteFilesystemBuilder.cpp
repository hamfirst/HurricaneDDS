
#include <experimental/filesystem>

#include "DDSWebsiteFilesystemBuilder.h"

namespace fs = std::experimental::filesystem;

struct MimeElement
{
  uint32_t m_FileTypeHash;
  const char * m_MimeType;
};

static MimeElement s_MimeList[] = 
{
  { COMPILE_TIME_CRC32_STR(".323"), "text/h323" },
  { COMPILE_TIME_CRC32_STR(".3g2"), "video/3gpp2" },
  { COMPILE_TIME_CRC32_STR(".3gp"), "video/3gpp" },
  { COMPILE_TIME_CRC32_STR(".3gp2"), "video/3gpp2" },
  { COMPILE_TIME_CRC32_STR(".3gpp"), "video/3gpp" },
  { COMPILE_TIME_CRC32_STR(".7z"), "application/x-7z-compressed" },
  { COMPILE_TIME_CRC32_STR(".aa"), "audio/audible" },
  { COMPILE_TIME_CRC32_STR(".AAC"), "audio/aac" },
  { COMPILE_TIME_CRC32_STR(".aaf"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".aax"), "audio/vnd.audible.aax" },
  { COMPILE_TIME_CRC32_STR(".ac3"), "audio/ac3" },
  { COMPILE_TIME_CRC32_STR(".aca"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".accda"), "application/msaccess.addin" },
  { COMPILE_TIME_CRC32_STR(".accdb"), "application/msaccess" },
  { COMPILE_TIME_CRC32_STR(".accdc"), "application/msaccess.cab" },
  { COMPILE_TIME_CRC32_STR(".accde"), "application/msaccess" },
  { COMPILE_TIME_CRC32_STR(".accdr"), "application/msaccess.runtime" },
  { COMPILE_TIME_CRC32_STR(".accdt"), "application/msaccess" },
  { COMPILE_TIME_CRC32_STR(".accdw"), "application/msaccess.webapplication" },
  { COMPILE_TIME_CRC32_STR(".accft"), "application/msaccess.ftemplate" },
  { COMPILE_TIME_CRC32_STR(".acx"), "application/internet-property-stream" },
  { COMPILE_TIME_CRC32_STR(".AddIn"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".ade"), "application/msaccess" },
  { COMPILE_TIME_CRC32_STR(".adobebridge"), "application/x-bridge-url" },
  { COMPILE_TIME_CRC32_STR(".adp"), "application/msaccess" },
  { COMPILE_TIME_CRC32_STR(".ADT"), "audio/vnd.dlna.adts" },
  { COMPILE_TIME_CRC32_STR(".ADTS"), "audio/aac" },
  { COMPILE_TIME_CRC32_STR(".afm"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".ai"), "application/postscript" },
  { COMPILE_TIME_CRC32_STR(".aif"), "audio/x-aiff" },
  { COMPILE_TIME_CRC32_STR(".aifc"), "audio/aiff" },
  { COMPILE_TIME_CRC32_STR(".aiff"), "audio/aiff" },
  { COMPILE_TIME_CRC32_STR(".air"), "application/vnd.adobe.air-application-installer-package+zip" },
  { COMPILE_TIME_CRC32_STR(".amc"), "application/x-mpeg" },
  { COMPILE_TIME_CRC32_STR(".application"), "application/x-ms-application" },
  { COMPILE_TIME_CRC32_STR(".art"), "image/x-jg" },
  { COMPILE_TIME_CRC32_STR(".asa"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".asax"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".ascx"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".asd"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".asf"), "video/x-ms-asf" },
  { COMPILE_TIME_CRC32_STR(".ashx"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".asi"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".asm"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".asmx"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".aspx"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".asr"), "video/x-ms-asf" },
  { COMPILE_TIME_CRC32_STR(".asx"), "video/x-ms-asf" },
  { COMPILE_TIME_CRC32_STR(".atom"), "application/atom+xml" },
  { COMPILE_TIME_CRC32_STR(".au"), "audio/basic" },
  { COMPILE_TIME_CRC32_STR(".avi"), "video/x-msvideo" },
  { COMPILE_TIME_CRC32_STR(".axs"), "application/olescript" },
  { COMPILE_TIME_CRC32_STR(".bas"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".bcpio"), "application/x-bcpio" },
  { COMPILE_TIME_CRC32_STR(".bin"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".bmp"), "image/bmp" },
  { COMPILE_TIME_CRC32_STR(".c"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".cab"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".caf"), "audio/x-caf" },
  { COMPILE_TIME_CRC32_STR(".calx"), "application/vnd.ms-office.calx" },
  { COMPILE_TIME_CRC32_STR(".cat"), "application/vnd.ms-pki.seccat" },
  { COMPILE_TIME_CRC32_STR(".cc"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".cd"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".cdda"), "audio/aiff" },
  { COMPILE_TIME_CRC32_STR(".cdf"), "application/x-cdf" },
  { COMPILE_TIME_CRC32_STR(".cer"), "application/x-x509-ca-cert" },
  { COMPILE_TIME_CRC32_STR(".chm"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".class"), "application/x-java-applet" },
  { COMPILE_TIME_CRC32_STR(".clp"), "application/x-msclip" },
  { COMPILE_TIME_CRC32_STR(".cmx"), "image/x-cmx" },
  { COMPILE_TIME_CRC32_STR(".cnf"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".cod"), "image/cis-cod" },
  { COMPILE_TIME_CRC32_STR(".config"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".contact"), "text/x-ms-contact" },
  { COMPILE_TIME_CRC32_STR(".coverage"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".cpio"), "application/x-cpio" },
  { COMPILE_TIME_CRC32_STR(".cpp"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".crd"), "application/x-mscardfile" },
  { COMPILE_TIME_CRC32_STR(".crl"), "application/pkix-crl" },
  { COMPILE_TIME_CRC32_STR(".crt"), "application/x-x509-ca-cert" },
  { COMPILE_TIME_CRC32_STR(".cs"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".csdproj"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".csh"), "application/x-csh" },
  { COMPILE_TIME_CRC32_STR(".csproj"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".css"), "text/css" },
  { COMPILE_TIME_CRC32_STR(".csv"), "text/csv" },
  { COMPILE_TIME_CRC32_STR(".cur"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".cxx"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".dat"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".datasource"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".dbproj"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".dcr"), "application/x-director" },
  { COMPILE_TIME_CRC32_STR(".def"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".deploy"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".der"), "application/x-x509-ca-cert" },
  { COMPILE_TIME_CRC32_STR(".dgml"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".dib"), "image/bmp" },
  { COMPILE_TIME_CRC32_STR(".dif"), "video/x-dv" },
  { COMPILE_TIME_CRC32_STR(".dir"), "application/x-director" },
  { COMPILE_TIME_CRC32_STR(".disco"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".dll"), "application/x-msdownload" },
  { COMPILE_TIME_CRC32_STR(".dll.config"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".dlm"), "text/dlm" },
  { COMPILE_TIME_CRC32_STR(".doc"), "application/msword" },
  { COMPILE_TIME_CRC32_STR(".docm"), "application/vnd.ms-word.document.macroEnabled.12" },
  { COMPILE_TIME_CRC32_STR(".docx"), "application/vnd.openxmlformats-officedocument.wordprocessingml.document" },
  { COMPILE_TIME_CRC32_STR(".dot"), "application/msword" },
  { COMPILE_TIME_CRC32_STR(".dotm"), "application/vnd.ms-word.template.macroEnabled.12" },
  { COMPILE_TIME_CRC32_STR(".dotx"), "application/vnd.openxmlformats-officedocument.wordprocessingml.template" },
  { COMPILE_TIME_CRC32_STR(".dsp"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".dsw"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".dtd"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".dtsConfig"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".dv"), "video/x-dv" },
  { COMPILE_TIME_CRC32_STR(".dvi"), "application/x-dvi" },
  { COMPILE_TIME_CRC32_STR(".dwf"), "drawing/x-dwf" },
  { COMPILE_TIME_CRC32_STR(".dwp"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".dxr"), "application/x-director" },
  { COMPILE_TIME_CRC32_STR(".eml"), "message/rfc822" },
  { COMPILE_TIME_CRC32_STR(".emz"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".eot"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".eps"), "application/postscript" },
  { COMPILE_TIME_CRC32_STR(".etl"), "application/etl" },
  { COMPILE_TIME_CRC32_STR(".etx"), "text/x-setext" },
  { COMPILE_TIME_CRC32_STR(".evy"), "application/envoy" },
  { COMPILE_TIME_CRC32_STR(".exe"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".exe.config"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".fdf"), "application/vnd.fdf" },
  { COMPILE_TIME_CRC32_STR(".fif"), "application/fractals" },
  { COMPILE_TIME_CRC32_STR(".filters"), "Application/xml" },
  { COMPILE_TIME_CRC32_STR(".fla"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".flr"), "x-world/x-vrml" },
  { COMPILE_TIME_CRC32_STR(".flv"), "video/x-flv" },
  { COMPILE_TIME_CRC32_STR(".fsscript"), "application/fsharp-script" },
  { COMPILE_TIME_CRC32_STR(".fsx"), "application/fsharp-script" },
  { COMPILE_TIME_CRC32_STR(".generictest"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".gif"), "image/gif" },
  { COMPILE_TIME_CRC32_STR(".group"), "text/x-ms-group" },
  { COMPILE_TIME_CRC32_STR(".gsm"), "audio/x-gsm" },
  { COMPILE_TIME_CRC32_STR(".gtar"), "application/x-gtar" },
  { COMPILE_TIME_CRC32_STR(".gz"), "application/x-gzip" },
  { COMPILE_TIME_CRC32_STR(".h"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".hdf"), "application/x-hdf" },
  { COMPILE_TIME_CRC32_STR(".hdml"), "text/x-hdml" },
  { COMPILE_TIME_CRC32_STR(".hhc"), "application/x-oleobject" },
  { COMPILE_TIME_CRC32_STR(".hhk"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".hhp"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".hlp"), "application/winhlp" },
  { COMPILE_TIME_CRC32_STR(".hpp"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".hqx"), "application/mac-binhex40" },
  { COMPILE_TIME_CRC32_STR(".hta"), "application/hta" },
  { COMPILE_TIME_CRC32_STR(".htc"), "text/x-component" },
  { COMPILE_TIME_CRC32_STR(".htm"), "text/html" },
  { COMPILE_TIME_CRC32_STR(".html"), "text/html" },
  { COMPILE_TIME_CRC32_STR(".htt"), "text/webviewhtml" },
  { COMPILE_TIME_CRC32_STR(".hxa"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".hxc"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".hxd"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".hxe"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".hxf"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".hxh"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".hxi"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".hxk"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".hxq"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".hxr"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".hxs"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".hxt"), "text/html" },
  { COMPILE_TIME_CRC32_STR(".hxv"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".hxw"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".hxx"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".i"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".ico"), "image/x-icon" },
  { COMPILE_TIME_CRC32_STR(".ics"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".idl"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".ief"), "image/ief" },
  { COMPILE_TIME_CRC32_STR(".iii"), "application/x-iphone" },
  { COMPILE_TIME_CRC32_STR(".inc"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".inf"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".inl"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".ins"), "application/x-internet-signup" },
  { COMPILE_TIME_CRC32_STR(".ipa"), "application/x-itunes-ipa" },
  { COMPILE_TIME_CRC32_STR(".ipg"), "application/x-itunes-ipg" },
  { COMPILE_TIME_CRC32_STR(".ipproj"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".ipsw"), "application/x-itunes-ipsw" },
  { COMPILE_TIME_CRC32_STR(".iqy"), "text/x-ms-iqy" },
  { COMPILE_TIME_CRC32_STR(".isp"), "application/x-internet-signup" },
  { COMPILE_TIME_CRC32_STR(".ite"), "application/x-itunes-ite" },
  { COMPILE_TIME_CRC32_STR(".itlp"), "application/x-itunes-itlp" },
  { COMPILE_TIME_CRC32_STR(".itms"), "application/x-itunes-itms" },
  { COMPILE_TIME_CRC32_STR(".itpc"), "application/x-itunes-itpc" },
  { COMPILE_TIME_CRC32_STR(".IVF"), "video/x-ivf" },
  { COMPILE_TIME_CRC32_STR(".jar"), "application/java-archive" },
  { COMPILE_TIME_CRC32_STR(".java"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".jck"), "application/liquidmotion" },
  { COMPILE_TIME_CRC32_STR(".jcz"), "application/liquidmotion" },
  { COMPILE_TIME_CRC32_STR(".jfif"), "image/pjpeg" },
  { COMPILE_TIME_CRC32_STR(".jnlp"), "application/x-java-jnlp-file" },
  { COMPILE_TIME_CRC32_STR(".jpb"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".jpe"), "image/jpeg" },
  { COMPILE_TIME_CRC32_STR(".jpeg"), "image/jpeg" },
  { COMPILE_TIME_CRC32_STR(".jpg"), "image/jpeg" },
  { COMPILE_TIME_CRC32_STR(".js"), "application/x-javascript" },
  { COMPILE_TIME_CRC32_STR(".json"), "application/json" },
  { COMPILE_TIME_CRC32_STR(".jsx"), "text/jscript" },
  { COMPILE_TIME_CRC32_STR(".jsxbin"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".latex"), "application/x-latex" },
  { COMPILE_TIME_CRC32_STR(".library-ms"), "application/windows-library+xml" },
  { COMPILE_TIME_CRC32_STR(".lit"), "application/x-ms-reader" },
  { COMPILE_TIME_CRC32_STR(".loadtest"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".lpk"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".lsf"), "video/x-la-asf" },
  { COMPILE_TIME_CRC32_STR(".lst"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".lsx"), "video/x-la-asf" },
  { COMPILE_TIME_CRC32_STR(".lzh"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".m13"), "application/x-msmediaview" },
  { COMPILE_TIME_CRC32_STR(".m14"), "application/x-msmediaview" },
  { COMPILE_TIME_CRC32_STR(".m1v"), "video/mpeg" },
  { COMPILE_TIME_CRC32_STR(".m2t"), "video/vnd.dlna.mpeg-tts" },
  { COMPILE_TIME_CRC32_STR(".m2ts"), "video/vnd.dlna.mpeg-tts" },
  { COMPILE_TIME_CRC32_STR(".m2v"), "video/mpeg" },
  { COMPILE_TIME_CRC32_STR(".m3u"), "audio/x-mpegurl" },
  { COMPILE_TIME_CRC32_STR(".m3u8"), "audio/x-mpegurl" },
  { COMPILE_TIME_CRC32_STR(".m4a"), "audio/m4a" },
  { COMPILE_TIME_CRC32_STR(".m4b"), "audio/m4b" },
  { COMPILE_TIME_CRC32_STR(".m4p"), "audio/m4p" },
  { COMPILE_TIME_CRC32_STR(".m4r"), "audio/x-m4r" },
  { COMPILE_TIME_CRC32_STR(".m4v"), "video/x-m4v" },
  { COMPILE_TIME_CRC32_STR(".mac"), "image/x-macpaint" },
  { COMPILE_TIME_CRC32_STR(".mak"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".man"), "application/x-troff-man" },
  { COMPILE_TIME_CRC32_STR(".manifest"), "application/x-ms-manifest" },
  { COMPILE_TIME_CRC32_STR(".map"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".master"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".mda"), "application/msaccess" },
  { COMPILE_TIME_CRC32_STR(".mdb"), "application/x-msaccess" },
  { COMPILE_TIME_CRC32_STR(".mde"), "application/msaccess" },
  { COMPILE_TIME_CRC32_STR(".mdp"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".me"), "application/x-troff-me" },
  { COMPILE_TIME_CRC32_STR(".mfp"), "application/x-shockwave-flash" },
  { COMPILE_TIME_CRC32_STR(".mht"), "message/rfc822" },
  { COMPILE_TIME_CRC32_STR(".mhtml"), "message/rfc822" },
  { COMPILE_TIME_CRC32_STR(".mid"), "audio/mid" },
  { COMPILE_TIME_CRC32_STR(".midi"), "audio/mid" },
  { COMPILE_TIME_CRC32_STR(".mix"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".mk"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".mmf"), "application/x-smaf" },
  { COMPILE_TIME_CRC32_STR(".mno"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".mny"), "application/x-msmoney" },
  { COMPILE_TIME_CRC32_STR(".mod"), "video/mpeg" },
  { COMPILE_TIME_CRC32_STR(".mov"), "video/quicktime" },
  { COMPILE_TIME_CRC32_STR(".movie"), "video/x-sgi-movie" },
  { COMPILE_TIME_CRC32_STR(".mp2"), "video/mpeg" },
  { COMPILE_TIME_CRC32_STR(".mp2v"), "video/mpeg" },
  { COMPILE_TIME_CRC32_STR(".mp3"), "audio/mpeg" },
  { COMPILE_TIME_CRC32_STR(".mp4"), "video/mp4" },
  { COMPILE_TIME_CRC32_STR(".mp4v"), "video/mp4" },
  { COMPILE_TIME_CRC32_STR(".mpa"), "video/mpeg" },
  { COMPILE_TIME_CRC32_STR(".mpe"), "video/mpeg" },
  { COMPILE_TIME_CRC32_STR(".mpeg"), "video/mpeg" },
  { COMPILE_TIME_CRC32_STR(".mpf"), "application/vnd.ms-mediapackage" },
  { COMPILE_TIME_CRC32_STR(".mpg"), "video/mpeg" },
  { COMPILE_TIME_CRC32_STR(".mpp"), "application/vnd.ms-project" },
  { COMPILE_TIME_CRC32_STR(".mpv2"), "video/mpeg" },
  { COMPILE_TIME_CRC32_STR(".mqv"), "video/quicktime" },
  { COMPILE_TIME_CRC32_STR(".ms"), "application/x-troff-ms" },
  { COMPILE_TIME_CRC32_STR(".msi"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".mso"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".mts"), "video/vnd.dlna.mpeg-tts" },
  { COMPILE_TIME_CRC32_STR(".mtx"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".mvb"), "application/x-msmediaview" },
  { COMPILE_TIME_CRC32_STR(".mvc"), "application/x-miva-compiled" },
  { COMPILE_TIME_CRC32_STR(".mxp"), "application/x-mmxp" },
  { COMPILE_TIME_CRC32_STR(".nc"), "application/x-netcdf" },
  { COMPILE_TIME_CRC32_STR(".nsc"), "video/x-ms-asf" },
  { COMPILE_TIME_CRC32_STR(".nws"), "message/rfc822" },
  { COMPILE_TIME_CRC32_STR(".ocx"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".oda"), "application/oda" },
  { COMPILE_TIME_CRC32_STR(".odc"), "text/x-ms-odc" },
  { COMPILE_TIME_CRC32_STR(".odh"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".odl"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".odp"), "application/vnd.oasis.opendocument.presentation" },
  { COMPILE_TIME_CRC32_STR(".ods"), "application/oleobject" },
  { COMPILE_TIME_CRC32_STR(".odt"), "application/vnd.oasis.opendocument.text" },
  { COMPILE_TIME_CRC32_STR(".one"), "application/onenote" },
  { COMPILE_TIME_CRC32_STR(".onea"), "application/onenote" },
  { COMPILE_TIME_CRC32_STR(".onepkg"), "application/onenote" },
  { COMPILE_TIME_CRC32_STR(".onetmp"), "application/onenote" },
  { COMPILE_TIME_CRC32_STR(".onetoc"), "application/onenote" },
  { COMPILE_TIME_CRC32_STR(".onetoc2"), "application/onenote" },
  { COMPILE_TIME_CRC32_STR(".orderedtest"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".osdx"), "application/opensearchdescription+xml" },
  { COMPILE_TIME_CRC32_STR(".p10"), "application/pkcs10" },
  { COMPILE_TIME_CRC32_STR(".p12"), "application/x-pkcs12" },
  { COMPILE_TIME_CRC32_STR(".p7b"), "application/x-pkcs7-certificates" },
  { COMPILE_TIME_CRC32_STR(".p7c"), "application/pkcs7-mime" },
  { COMPILE_TIME_CRC32_STR(".p7m"), "application/pkcs7-mime" },
  { COMPILE_TIME_CRC32_STR(".p7r"), "application/x-pkcs7-certreqresp" },
  { COMPILE_TIME_CRC32_STR(".p7s"), "application/pkcs7-signature" },
  { COMPILE_TIME_CRC32_STR(".pbm"), "image/x-portable-bitmap" },
  { COMPILE_TIME_CRC32_STR(".pcast"), "application/x-podcast" },
  { COMPILE_TIME_CRC32_STR(".pct"), "image/pict" },
  { COMPILE_TIME_CRC32_STR(".pcx"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".pcz"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".pdf"), "application/pdf" },
  { COMPILE_TIME_CRC32_STR(".pfb"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".pfm"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".pfx"), "application/x-pkcs12" },
  { COMPILE_TIME_CRC32_STR(".pgm"), "image/x-portable-graymap" },
  { COMPILE_TIME_CRC32_STR(".pic"), "image/pict" },
  { COMPILE_TIME_CRC32_STR(".pict"), "image/pict" },
  { COMPILE_TIME_CRC32_STR(".pkgdef"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".pkgundef"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".pko"), "application/vnd.ms-pki.pko" },
  { COMPILE_TIME_CRC32_STR(".pls"), "audio/scpls" },
  { COMPILE_TIME_CRC32_STR(".pma"), "application/x-perfmon" },
  { COMPILE_TIME_CRC32_STR(".pmc"), "application/x-perfmon" },
  { COMPILE_TIME_CRC32_STR(".pml"), "application/x-perfmon" },
  { COMPILE_TIME_CRC32_STR(".pmr"), "application/x-perfmon" },
  { COMPILE_TIME_CRC32_STR(".pmw"), "application/x-perfmon" },
  { COMPILE_TIME_CRC32_STR(".png"), "image/png" },
  { COMPILE_TIME_CRC32_STR(".pnm"), "image/x-portable-anymap" },
  { COMPILE_TIME_CRC32_STR(".pnt"), "image/x-macpaint" },
  { COMPILE_TIME_CRC32_STR(".pntg"), "image/x-macpaint" },
  { COMPILE_TIME_CRC32_STR(".pnz"), "image/png" },
  { COMPILE_TIME_CRC32_STR(".pot"), "application/vnd.ms-powerpoint" },
  { COMPILE_TIME_CRC32_STR(".potm"), "application/vnd.ms-powerpoint.template.macroEnabled.12" },
  { COMPILE_TIME_CRC32_STR(".potx"), "application/vnd.openxmlformats-officedocument.presentationml.template" },
  { COMPILE_TIME_CRC32_STR(".ppa"), "application/vnd.ms-powerpoint" },
  { COMPILE_TIME_CRC32_STR(".ppam"), "application/vnd.ms-powerpoint.addin.macroEnabled.12" },
  { COMPILE_TIME_CRC32_STR(".ppm"), "image/x-portable-pixmap" },
  { COMPILE_TIME_CRC32_STR(".pps"), "application/vnd.ms-powerpoint" },
  { COMPILE_TIME_CRC32_STR(".ppsm"), "application/vnd.ms-powerpoint.slideshow.macroEnabled.12" },
  { COMPILE_TIME_CRC32_STR(".ppsx"), "application/vnd.openxmlformats-officedocument.presentationml.slideshow" },
  { COMPILE_TIME_CRC32_STR(".ppt"), "application/vnd.ms-powerpoint" },
  { COMPILE_TIME_CRC32_STR(".pptm"), "application/vnd.ms-powerpoint.presentation.macroEnabled.12" },
  { COMPILE_TIME_CRC32_STR(".pptx"), "application/vnd.openxmlformats-officedocument.presentationml.presentation" },
  { COMPILE_TIME_CRC32_STR(".prf"), "application/pics-rules" },
  { COMPILE_TIME_CRC32_STR(".prm"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".prx"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".ps"), "application/postscript" },
  { COMPILE_TIME_CRC32_STR(".psc1"), "application/PowerShell" },
  { COMPILE_TIME_CRC32_STR(".psd"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".psess"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".psm"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".psp"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".pub"), "application/x-mspublisher" },
  { COMPILE_TIME_CRC32_STR(".pwz"), "application/vnd.ms-powerpoint" },
  { COMPILE_TIME_CRC32_STR(".qht"), "text/x-html-insertion" },
  { COMPILE_TIME_CRC32_STR(".qhtm"), "text/x-html-insertion" },
  { COMPILE_TIME_CRC32_STR(".qt"), "video/quicktime" },
  { COMPILE_TIME_CRC32_STR(".qti"), "image/x-quicktime" },
  { COMPILE_TIME_CRC32_STR(".qtif"), "image/x-quicktime" },
  { COMPILE_TIME_CRC32_STR(".qtl"), "application/x-quicktimeplayer" },
  { COMPILE_TIME_CRC32_STR(".qxd"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".ra"), "audio/x-pn-realaudio" },
  { COMPILE_TIME_CRC32_STR(".ram"), "audio/x-pn-realaudio" },
  { COMPILE_TIME_CRC32_STR(".rar"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".ras"), "image/x-cmu-raster" },
  { COMPILE_TIME_CRC32_STR(".rat"), "application/rat-file" },
  { COMPILE_TIME_CRC32_STR(".rc"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".rc2"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".rct"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".rdlc"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".resx"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".rf"), "image/vnd.rn-realflash" },
  { COMPILE_TIME_CRC32_STR(".rgb"), "image/x-rgb" },
  { COMPILE_TIME_CRC32_STR(".rgs"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".rm"), "application/vnd.rn-realmedia" },
  { COMPILE_TIME_CRC32_STR(".rmi"), "audio/mid" },
  { COMPILE_TIME_CRC32_STR(".rmp"), "application/vnd.rn-rn_music_package" },
  { COMPILE_TIME_CRC32_STR(".roff"), "application/x-troff" },
  { COMPILE_TIME_CRC32_STR(".rpm"), "audio/x-pn-realaudio-plugin" },
  { COMPILE_TIME_CRC32_STR(".rqy"), "text/x-ms-rqy" },
  { COMPILE_TIME_CRC32_STR(".rtf"), "application/rtf" },
  { COMPILE_TIME_CRC32_STR(".rtx"), "text/richtext" },
  { COMPILE_TIME_CRC32_STR(".ruleset"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".s"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".safariextz"), "application/x-safari-safariextz" },
  { COMPILE_TIME_CRC32_STR(".scd"), "application/x-msschedule" },
  { COMPILE_TIME_CRC32_STR(".sct"), "text/scriptlet" },
  { COMPILE_TIME_CRC32_STR(".sd2"), "audio/x-sd2" },
  { COMPILE_TIME_CRC32_STR(".sdp"), "application/sdp" },
  { COMPILE_TIME_CRC32_STR(".sea"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".searchConnector-ms"), "application/windows-search-connector+xml" },
  { COMPILE_TIME_CRC32_STR(".setpay"), "application/set-payment-initiation" },
  { COMPILE_TIME_CRC32_STR(".setreg"), "application/set-registration-initiation" },
  { COMPILE_TIME_CRC32_STR(".settings"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".sgimb"), "application/x-sgimb" },
  { COMPILE_TIME_CRC32_STR(".sgml"), "text/sgml" },
  { COMPILE_TIME_CRC32_STR(".sh"), "application/x-sh" },
  { COMPILE_TIME_CRC32_STR(".shar"), "application/x-shar" },
  { COMPILE_TIME_CRC32_STR(".shtml"), "text/html" },
  { COMPILE_TIME_CRC32_STR(".sit"), "application/x-stuffit" },
  { COMPILE_TIME_CRC32_STR(".sitemap"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".skin"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".sldm"), "application/vnd.ms-powerpoint.slide.macroEnabled.12" },
  { COMPILE_TIME_CRC32_STR(".sldx"), "application/vnd.openxmlformats-officedocument.presentationml.slide" },
  { COMPILE_TIME_CRC32_STR(".slk"), "application/vnd.ms-excel" },
  { COMPILE_TIME_CRC32_STR(".sln"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".slupkg-ms"), "application/x-ms-license" },
  { COMPILE_TIME_CRC32_STR(".smd"), "audio/x-smd" },
  { COMPILE_TIME_CRC32_STR(".smi"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".smx"), "audio/x-smd" },
  { COMPILE_TIME_CRC32_STR(".smz"), "audio/x-smd" },
  { COMPILE_TIME_CRC32_STR(".snd"), "audio/basic" },
  { COMPILE_TIME_CRC32_STR(".snippet"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".snp"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".sol"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".sor"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".spc"), "application/x-pkcs7-certificates" },
  { COMPILE_TIME_CRC32_STR(".spl"), "application/futuresplash" },
  { COMPILE_TIME_CRC32_STR(".src"), "application/x-wais-source" },
  { COMPILE_TIME_CRC32_STR(".srf"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".SSISDeploymentManifest"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".ssm"), "application/streamingmedia" },
  { COMPILE_TIME_CRC32_STR(".sst"), "application/vnd.ms-pki.certstore" },
  { COMPILE_TIME_CRC32_STR(".stl"), "application/vnd.ms-pki.stl" },
  { COMPILE_TIME_CRC32_STR(".sv4cpio"), "application/x-sv4cpio" },
  { COMPILE_TIME_CRC32_STR(".sv4crc"), "application/x-sv4crc" },
  { COMPILE_TIME_CRC32_STR(".svc"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".swf"), "application/x-shockwave-flash" },
  { COMPILE_TIME_CRC32_STR(".t"), "application/x-troff" },
  { COMPILE_TIME_CRC32_STR(".tar"), "application/x-tar" },
  { COMPILE_TIME_CRC32_STR(".tcl"), "application/x-tcl" },
  { COMPILE_TIME_CRC32_STR(".testrunconfig"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".testsettings"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".tex"), "application/x-tex" },
  { COMPILE_TIME_CRC32_STR(".texi"), "application/x-texinfo" },
  { COMPILE_TIME_CRC32_STR(".texinfo"), "application/x-texinfo" },
  { COMPILE_TIME_CRC32_STR(".tgz"), "application/x-compressed" },
  { COMPILE_TIME_CRC32_STR(".thmx"), "application/vnd.ms-officetheme" },
  { COMPILE_TIME_CRC32_STR(".thn"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".tif"), "image/tiff" },
  { COMPILE_TIME_CRC32_STR(".tiff"), "image/tiff" },
  { COMPILE_TIME_CRC32_STR(".tlh"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".tli"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".toc"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".tr"), "application/x-troff" },
  { COMPILE_TIME_CRC32_STR(".trm"), "application/x-msterminal" },
  { COMPILE_TIME_CRC32_STR(".trx"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".ts"), "video/vnd.dlna.mpeg-tts" },
  { COMPILE_TIME_CRC32_STR(".tsv"), "text/tab-separated-values" },
  { COMPILE_TIME_CRC32_STR(".ttf"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".tts"), "video/vnd.dlna.mpeg-tts" },
  { COMPILE_TIME_CRC32_STR(".txt"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".u32"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".uls"), "text/iuls" },
  { COMPILE_TIME_CRC32_STR(".user"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".ustar"), "application/x-ustar" },
  { COMPILE_TIME_CRC32_STR(".vb"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".vbdproj"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".vbk"), "video/mpeg" },
  { COMPILE_TIME_CRC32_STR(".vbproj"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".vbs"), "text/vbscript" },
  { COMPILE_TIME_CRC32_STR(".vcf"), "text/x-vcard" },
  { COMPILE_TIME_CRC32_STR(".vcproj"), "Application/xml" },
  { COMPILE_TIME_CRC32_STR(".vcs"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".vcxproj"), "Application/xml" },
  { COMPILE_TIME_CRC32_STR(".vddproj"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".vdp"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".vdproj"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".vdx"), "application/vnd.ms-visio.viewer" },
  { COMPILE_TIME_CRC32_STR(".vml"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".vscontent"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".vsct"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".vsd"), "application/vnd.visio" },
  { COMPILE_TIME_CRC32_STR(".vsi"), "application/ms-vsi" },
  { COMPILE_TIME_CRC32_STR(".vsix"), "application/vsix" },
  { COMPILE_TIME_CRC32_STR(".vsixlangpack"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".vsixmanifest"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".vsmdi"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".vspscc"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".vss"), "application/vnd.visio" },
  { COMPILE_TIME_CRC32_STR(".vsscc"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".vssettings"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".vssscc"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".vst"), "application/vnd.visio" },
  { COMPILE_TIME_CRC32_STR(".vstemplate"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".vsto"), "application/x-ms-vsto" },
  { COMPILE_TIME_CRC32_STR(".vsw"), "application/vnd.visio" },
  { COMPILE_TIME_CRC32_STR(".vsx"), "application/vnd.visio" },
  { COMPILE_TIME_CRC32_STR(".vtx"), "application/vnd.visio" },
  { COMPILE_TIME_CRC32_STR(".wav"), "audio/wav" },
  { COMPILE_TIME_CRC32_STR(".wave"), "audio/wav" },
  { COMPILE_TIME_CRC32_STR(".wax"), "audio/x-ms-wax" },
  { COMPILE_TIME_CRC32_STR(".wbk"), "application/msword" },
  { COMPILE_TIME_CRC32_STR(".wbmp"), "image/vnd.wap.wbmp" },
  { COMPILE_TIME_CRC32_STR(".wcm"), "application/vnd.ms-works" },
  { COMPILE_TIME_CRC32_STR(".wdb"), "application/vnd.ms-works" },
  { COMPILE_TIME_CRC32_STR(".wdp"), "image/vnd.ms-photo" },
  { COMPILE_TIME_CRC32_STR(".webarchive"), "application/x-safari-webarchive" },
  { COMPILE_TIME_CRC32_STR(".webtest"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".wiq"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".wiz"), "application/msword" },
  { COMPILE_TIME_CRC32_STR(".wks"), "application/vnd.ms-works" },
  { COMPILE_TIME_CRC32_STR(".WLMP"), "application/wlmoviemaker" },
  { COMPILE_TIME_CRC32_STR(".wlpginstall"), "application/x-wlpg-detect" },
  { COMPILE_TIME_CRC32_STR(".wlpginstall3"), "application/x-wlpg3-detect" },
  { COMPILE_TIME_CRC32_STR(".wm"), "video/x-ms-wm" },
  { COMPILE_TIME_CRC32_STR(".wma"), "audio/x-ms-wma" },
  { COMPILE_TIME_CRC32_STR(".wmd"), "application/x-ms-wmd" },
  { COMPILE_TIME_CRC32_STR(".wmf"), "application/x-msmetafile" },
  { COMPILE_TIME_CRC32_STR(".wml"), "text/vnd.wap.wml" },
  { COMPILE_TIME_CRC32_STR(".wmlc"), "application/vnd.wap.wmlc" },
  { COMPILE_TIME_CRC32_STR(".wmls"), "text/vnd.wap.wmlscript" },
  { COMPILE_TIME_CRC32_STR(".wmlsc"), "application/vnd.wap.wmlscriptc" },
  { COMPILE_TIME_CRC32_STR(".wmp"), "video/x-ms-wmp" },
  { COMPILE_TIME_CRC32_STR(".wmv"), "video/x-ms-wmv" },
  { COMPILE_TIME_CRC32_STR(".wmx"), "video/x-ms-wmx" },
  { COMPILE_TIME_CRC32_STR(".wmz"), "application/x-ms-wmz" },
  { COMPILE_TIME_CRC32_STR(".wpl"), "application/vnd.ms-wpl" },
  { COMPILE_TIME_CRC32_STR(".wps"), "application/vnd.ms-works" },
  { COMPILE_TIME_CRC32_STR(".wri"), "application/x-mswrite" },
  { COMPILE_TIME_CRC32_STR(".wrl"), "x-world/x-vrml" },
  { COMPILE_TIME_CRC32_STR(".wrz"), "x-world/x-vrml" },
  { COMPILE_TIME_CRC32_STR(".wsc"), "text/scriptlet" },
  { COMPILE_TIME_CRC32_STR(".wsdl"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".wvx"), "video/x-ms-wvx" },
  { COMPILE_TIME_CRC32_STR(".x"), "application/directx" },
  { COMPILE_TIME_CRC32_STR(".xaf"), "x-world/x-vrml" },
  { COMPILE_TIME_CRC32_STR(".xaml"), "application/xaml+xml" },
  { COMPILE_TIME_CRC32_STR(".xap"), "application/x-silverlight-app" },
  { COMPILE_TIME_CRC32_STR(".xbap"), "application/x-ms-xbap" },
  { COMPILE_TIME_CRC32_STR(".xbm"), "image/x-xbitmap" },
  { COMPILE_TIME_CRC32_STR(".xdr"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".xht"), "application/xhtml+xml" },
  { COMPILE_TIME_CRC32_STR(".xhtml"), "application/xhtml+xml" },
  { COMPILE_TIME_CRC32_STR(".xla"), "application/vnd.ms-excel" },
  { COMPILE_TIME_CRC32_STR(".xlam"), "application/vnd.ms-excel.addin.macroEnabled.12" },
  { COMPILE_TIME_CRC32_STR(".xlc"), "application/vnd.ms-excel" },
  { COMPILE_TIME_CRC32_STR(".xld"), "application/vnd.ms-excel" },
  { COMPILE_TIME_CRC32_STR(".xlk"), "application/vnd.ms-excel" },
  { COMPILE_TIME_CRC32_STR(".xll"), "application/vnd.ms-excel" },
  { COMPILE_TIME_CRC32_STR(".xlm"), "application/vnd.ms-excel" },
  { COMPILE_TIME_CRC32_STR(".xls"), "application/vnd.ms-excel" },
  { COMPILE_TIME_CRC32_STR(".xlsb"), "application/vnd.ms-excel.sheet.binary.macroEnabled.12" },
  { COMPILE_TIME_CRC32_STR(".xlsm"), "application/vnd.ms-excel.sheet.macroEnabled.12" },
  { COMPILE_TIME_CRC32_STR(".xlsx"), "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet" },
  { COMPILE_TIME_CRC32_STR(".xlt"), "application/vnd.ms-excel" },
  { COMPILE_TIME_CRC32_STR(".xltm"), "application/vnd.ms-excel.template.macroEnabled.12" },
  { COMPILE_TIME_CRC32_STR(".xltx"), "application/vnd.openxmlformats-officedocument.spreadsheetml.template" },
  { COMPILE_TIME_CRC32_STR(".xlw"), "application/vnd.ms-excel" },
  { COMPILE_TIME_CRC32_STR(".xml"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".xmta"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".xof"), "x-world/x-vrml" },
  { COMPILE_TIME_CRC32_STR(".XOML"), "text/plain" },
  { COMPILE_TIME_CRC32_STR(".xpm"), "image/x-xpixmap" },
  { COMPILE_TIME_CRC32_STR(".xps"), "application/vnd.ms-xpsdocument" },
  { COMPILE_TIME_CRC32_STR(".xrm-ms"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".xsc"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".xsd"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".xsf"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".xsl"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".xslt"), "text/xml" },
  { COMPILE_TIME_CRC32_STR(".xsn"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".xss"), "application/xml" },
  { COMPILE_TIME_CRC32_STR(".xtp"), "application/octet-stream" },
  { COMPILE_TIME_CRC32_STR(".xwd"), "image/x-xwindowdump" },
  { COMPILE_TIME_CRC32_STR(".z"), "application/x-compress" },
  { COMPILE_TIME_CRC32_STR(".zip"), "application/x-zip-compressed" },
};

DDSWebsiteFilesystemBuilder::DDSWebsiteFilesystemBuilder()
{
  int num_mimes = sizeof(s_MimeList) / sizeof(s_MimeList[0]);
  for (int index = 0; index < num_mimes; index++)
  {
    m_MimeTypes.emplace(std::make_pair(s_MimeList[index].m_FileTypeHash, s_MimeList[index].m_MimeType));
  }
}

void DDSWebsiteFilesystemBuilder::AddDirectory(const char * dir_path, const char * base_url)
{
  for (auto & file : fs::directory_iterator(dir_path))
  {
    if (fs::is_directory(file))
    {
      auto file_path = file.path();
      std::string stem = file_path.filename().string();

      if (stem[0] == '.')
      {
        continue;
      }

      std::string sub_url = base_url;
      sub_url += stem;
      sub_url += '/';

      AddDirectory(file_path.string().data(), sub_url.data());
    }
    else if (fs::is_regular_file(file))
    {
      auto file_path = file.path();
      std::string stem = file_path.filename().string();

      if (stem[0] == '.')
      {
        continue;
      }

      std::string sub_url = base_url;
      sub_url += stem;

      AddFile(file_path.string().data(), sub_url.data());
    }
  }
}

void DDSWebsiteFilesystemBuilder::AddFile(const char * file_path, const char * url)
{
  FILE * fp = fopen(file_path, "rb");
  if (fp == nullptr)
  {
    return;
  }

  fseek(fp, 0, SEEK_END);
  std::size_t len = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  std::vector<char> buffer(len);
  fread(buffer.data(), len, 1, fp);
  fclose(fp);

  const char * extension = nullptr;
  auto period = strchr(url, '.');

  while (period)
  {
    extension = period + 1;
    period = strchr(extension, '.');
  }

  const char * mime_type = extension != nullptr ? GetMimeTimeForFileExtension(extension) : nullptr;

  m_MappedFiles.emplace(std::make_pair(url, FileData{ std::move(buffer), mime_type }));
}

void DDSWebsiteFilesystemBuilder::AddMemFile(const char * url, const void * data, std::size_t len)
{
  std::vector<char> buffer(len);
  memcpy(buffer.data(), data, len);

  const char * extension = nullptr;
  auto period = strchr(url, '.');

  while (period)
  {
    extension = period + 1;
    period = strchr(extension, '.');
  }

  const char * mime_type = extension != nullptr ? GetMimeTimeForFileExtension(extension) : nullptr;

  m_MappedFiles.emplace(std::make_pair(url, FileData{ std::move(buffer), mime_type }));
}

const char * DDSWebsiteFilesystemBuilder::GetMimeTimeForFileExtension(const char * file_extension)
{
  auto hash = crc32(file_extension);
  auto itr = m_MimeTypes.find(hash);

  return itr == m_MimeTypes.end() ? nullptr : itr->second;
}
