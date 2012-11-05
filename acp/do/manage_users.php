<?php
$action = $_GET['action'];
$id = $_GET['id'];
$del = $_GET['del'];
$really = $_GET['really'];

require("includes/mysql_connect.inc");
mysql_select_db("usr_web4_5", $con);

if($action == 'add')
{
	if($_POST['username'] != null and $_POST['password'] != null)
	{
		$query = mysql_query("INSERT INTO users (username,password) VALUES ('".$_POST['username']."','".$_POST['password']."')");
		echo '
		Benutzer '.$_POST['username'].' wurde erstellt.<br />
		';
	}
	echo '
	<form method="post" action="">
	Benutzername: <input type="text" name="username" size="50" /><br />
	Passwort: <input type="password" name="password" size="50" /><br />
	<input type="submit" name="absenden" value="Absenden" />
	</form>
	';
}

else if($action == 'edit')
{
	if($_POST['username'] != null and $_POST['password'] != null)
	{
		mysql_query("UPDATE users Set username='".$_POST['username']."', password='".$_POST['password']."' WHERE id='".$id."'");
		echo '<p>Benutzer wurde bearbeitet.</p>';
	}
	$query = mysql_query("SELECT * FROM users WHERE id='".$id."'",$con);
	$data = mysql_fetch_object($query);
	
	echo '
	<h1>Benutzer bearbeiten</h1>
	<form method="post" action="">
	Benutzername: <input type="text" name="username" size="50" value="'.$data->username.'" /><br />
	Passwort: <input type="password" name="password" size="50" value="'.$data->password.'" /><br />
	<input type="submit" name="absenden" value="Absenden" />
	</form>
	';
}

//delete
if( $del != null and $really != 1)
{
	echo '<p>Benutzer mit der ID '.$del.' wirklich löschen?<br />';
	echo '<a href="?do=manage_users&amp;del='.$del.'&amp;really=1">Ja</a> - ';
	echo '<a href="?do=manage_users">Nein</a></p>';
}
if($del != null and $really == 1)
{
	mysql_query("DELETE FROM users WHERE id = '".$del."'");
	echo '<p>Der Benutzer mit der ID '.$del.' wurde gelöscht.</p>';
}

$query = mysql_query("SELECT * FROM users ORDER BY id");
echo '<table>';
while($row = mysql_fetch_object($query))
{
  echo '<tr><td>'.$row->id.'</td><td>'.$row->username.'</td><td><a href="?do=manage_users&amp;action=edit&amp;id='.$row->id.'">bearbeiten</a></td><td><a href="?do=manage_users&amp;del='.$row->id.'">x</a></td></tr>';
}
echo '</table>';

if($action != 'add')
{
	echo '<p><a href="?do=manage_users&amp;action=add">Neuen Benutzer erstellen</a></p>';
}

mysql_close($con);
?>