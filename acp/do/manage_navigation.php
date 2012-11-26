<?php
$action = $_GET['action'];
$id = $_GET['id'];
$del = $_GET['del'];
$really = $_GET['really'];

require("includes/mysql_connect.inc");
mysql_select_db("usr_web4_5", $con);

if($action == 'add')
{
	if($_POST['title'] != null and $_POST['url'] != null)
	{
		$query = mysql_query("INSERT INTO navigation (title,url) VALUES ('".$_POST['title']."','".$_POST['url']."')");
		echo '
		Link '.$_POST['title'].' wurde erstellt.<br />
		';
	}
	echo '
	<form method="post" action="">
	Titel: <input type="text" name="title" size="50" /><br />
	URL: <input type="text" name="url" size="50" /><br />
	<input type="submit" name="absenden" value="Absenden" />
	</form>
	';
}
elseif($action == 'edit')
{
	if($_POST['title'] != null and $_POST['url'] != null)
	{
		mysql_query("UPDATE navigation Set title='".$_POST['title']."', url='".$_POST['url']."' WHERE id='".$id."'");
		echo '<p>Link wurde bearbeitet.</p>';
	}
	$query = mysql_query("SELECT * FROM navigation WHERE id='".$id."'",$con);
	$data = mysql_fetch_object($query);
	
	echo '
	<h1>Link bearbeiten</h1>
	<form method="post" action="">
	Titel: <input type="text" name="title" size="50" value="'.$data->title.'" /><br />
	URL: <input type="text" name="url" size="50" value="'.$data->url.'" /><br />
	<input type="submit" name="absenden" value="Absenden" />
	</form>
	';
}

//delete
if( $del != null and $really != 1)
{
	echo '<p>Link mit der ID '.$del.' wirklich löschen?<br />';
	echo '<a href="?do=manage_navigation&amp;del='.$del.'&amp;really=1">Ja</a> - ';
	echo '<a href="?do=manage_navigation">Nein</a></p>';
}
if($del != null and $really == 1)
{
	mysql_query("DELETE FROM navigation WHERE id = '".$del."'");
	echo '<p>Der Link mit der ID '.$del.' wurde gelöscht.</p>';
}

$query = mysql_query("SELECT * FROM navigation ORDER BY id");
echo '<table>';
while($row = mysql_fetch_object($query))
{
  echo '<tr><td>'.$row->id.'</td><td><a href="/'.$row->url.'">'.$row->title.'</a></td><td><a href="?do=manage_navigation&amp;action=edit&amp;id='.$row->id.'">bearbeiten</a></td><td><a href="?do=manage_navigation&amp;del='.$row->id.'">x</a></td></tr>';
}
echo '</table>';

if($action != 'add')
{
	echo '
	<p><a href="?do=manage_navigation&amp;action=add">Neuen Link erstellen</a></p>
	';
}

mysql_close($con);
?>
