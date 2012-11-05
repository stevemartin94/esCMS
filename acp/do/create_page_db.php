<?php
require('includes/mysql_connect.inc');

$umlaute = array("/ä/","/ö/","/ü/","/Ä/","/Ö/","/Ü/","/ß/"); 
$replace = array("ae","oe","ue","Ae","Oe","Ue","ss");

$fulltitle = utf8_decode($_POST['fulltitle']);
$fulltitle = preg_replace($umlaute, $replace, $fulltitle);
$fulltitle = utf8_encode($fulltitle);
$title = trim(preg_replace("/[^\w]+/","_",html_entity_decode($fulltitle)), '_');
$sql = "INSERT INTO pages (title,fulltitle,content) VALUES ('".$title."','".$_POST['fulltitle']."','".$_POST['content']."')";
mysql_query($sql,$con);
mysql_close($con);
?>

Seite <? echo $_POST['fulltitle'] ?> wurde erstellt.<br />
<a href="/?p=<? echo $title ?>">Seite ansehen</a>
<p><a href="?do=manage_pages">Seiten verwalten</a></p>