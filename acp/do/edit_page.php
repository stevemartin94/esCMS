<?php
$id = $_GET['id'];
require('includes/mysql_connect.inc');
mysql_select_db("usr_web4_5",$con);
if($_POST['content'] != null)
{
	mysql_query("UPDATE pages Set fulltitle='".$_POST['fulltitle']."', content='".$_POST['content']."' WHERE id='".$id."'");
	echo '<p>Seite wurde bearbeitet.</p>';
}
$query = mysql_query("SELECT * FROM pages WHERE id='".$id."'",$con);
$data = mysql_fetch_object($query);
?>

<h1>Seite bearbeiten</h1>
<form method="post" action="">
Seitentitel: <input type="text" name="fulltitle" size="50" value="<? echo $data->fulltitle ?>" /><br />
Inhalt:<br />
<textarea name="content" cols="50" rows="10"><? echo $data->content ?></textarea><br />
<input type="submit" name="absenden" value="Absenden" />
</form>
<a href="?do=manage_pages">Seiten verwalten</a>

<?php mysql_close($con); ?>