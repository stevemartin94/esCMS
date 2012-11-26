<?php
header('Content-Type: text/html; charset=utf-8');

// time to load
$time = microtime();
$time = explode(' ', $time);
$time = $time[1] + $time[0];
$start = $time;

// get page url
function curPageURL() {
 $pageURL = 'http';
 if ($_SERVER["HTTPS"] == "on") {$pageURL .= "s";}
 $pageURL .= "://";
 if ($_SERVER["SERVER_PORT"] != "80") {
  $pageURL .= $_SERVER["SERVER_NAME"].":".$_SERVER["SERVER_PORT"].$_SERVER["REQUEST_URI"];
 } else {
  $pageURL .= $_SERVER["SERVER_NAME"].$_SERVER["REQUEST_URI"];
 }
 return $pageURL;
}

// set desktop or mobile style
$style = get_getvar('style');
if($style != NULL)
{
    setcookie("SiteStyle", $style, time()+60*60*24*365);
}
elseif (get_cookievar('style') != NULL)
{
    $style = get_cookievar('style');
}
else
{
    require('includes/check_mobile.inc');
    if(check_mobile()) $style = 'mobile';
}

// set site width
$width = get_getvar('width');
$stdwidth = '1000px';
if($width != NULL)
{
    setcookie("SiteWidth", $width, time()+60*60*24*365);
}
elseif(get_cookievar('SiteWidth') != NULL)
{
    $width = get_cookievar('SiteWidth');
}
else
{
    $width = $stdwidth;
}

$fulltitle = $page->fulltitle;
?>
<!DOCTYPE html>
<html xml:lang="de" lang="de" xmlns="http://www.w3.org/1999/xhtml">
    <head>
        <title><?php if($fulltitle != NULL) {
                         echo $fulltitle . ' - ';
                     }
                     echo htmlspecialchars($config['site_name']); ?></title>
        <?php
        if($style != 'mobile')
        {
            echo '
            <script type="text/javascript" src="js/lytebox.js"></script>
            <script type="text/javascript" src="js/main.js"></script>
            ';
        }
        ?>

        <style type="text/css">
            <?php
            if($style == 'mobile')
            {
                echo '
                @import url("styles/mobile.css") handheld;
                ';
            }
            else
            {
                echo '
                @import url("styles/main.css") screen;
                @import url("styles/lytebox.css");
                ';
            }
            ?>
            
            @import url("styles/print.css") print;

            #wrap
            {
                width: <?php echo htmlspecialchars($width); ?>;
            }
        </style>

        <meta http-equiv="content-type" content="text/html; charset=utf-8" />
        <meta name="robots" content="index,follow" />
        <link rel="apple-touch-icon" href="images/ios_icon.png" />
        <link rel="apple-touch-startup-image" href="images/ios_splash.png" />
        <meta name="apple-mobile-web-app-capable" content="yes" />
        <meta name="apple-mobile-web-app-status-bar-style" content="black-translucent" />
        <meta name="viewport" content = "width = device-width, user-scalable = yes" />

    </head>
    <body>
    <div id="wrap">
    <div id="main">
    <header>
    </header>
    <nav>
    <?php require("includes/nav.inc"); ?>
    </nav>
    <div id="sitecontrols">
    Breite: 
    <script type="text/javascript">
        document.write("<a href=\"#\" onclick=\"setWidth('100%')\">100%</a> - <a href=\"#\" onclick=\"setWidth('1000px')\">1000px</a>");
    </script>
    <noscript>
    <a href="?width=100">100%</a> - <a href="?width=1000px">1000px</a>
    </noscript>
    </div>
    <article>