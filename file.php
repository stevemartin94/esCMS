<?php
header('Content-Type: text/html; charset=utf-8');

$time = microtime();
$time = explode(' ', $time);
$time = $time[1] + $time[0];
$start = $time;

$p = $_GET['p'];
if($p == null)
{
	$p = index;
}

require("includes/header.inc");


if(file_exists("pages/".$p.".page"))
{
	require("pages/".$p.".page");
}
else
{
	require("pages/404.page");
}

$time = microtime();
$time = explode(' ', $time);
$time = $time[1] + $time[0];
$finish = $time;
$total_time = round(($finish - $start), 4);

require("includes/footer.inc");
?>