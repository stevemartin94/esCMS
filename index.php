<?php
require("includes/header.inc");

require('includes/mysql_connect.inc');

$query = mysql_query("SELECT * FROM pages WHERE ".$do." = '".$par."'");
$data = mysql_fetch_object($query);
// Error 404
if($data == null)
{
	$query = mysql_query("SELECT * FROM pages WHERE title = '404'");
	$data = mysql_fetch_object($query);
	echo $data->content;
}
else
{
    echo '<h1>'.$data->fulltitle.'</h1>';
	echo $data->content;
}

mysql_close($con);

require("includes/footer.inc");
?>