<h1>Seiten verwalten</h1>
<?
$del = $_GET['del'];
$really = $_GET['really'];
require('includes/mysql_connect.inc');
//delete
if( $del != null and $really != 1)
{
	echo '<p>Seite mit der ID '.$del.' wirklich löschen?<br />';
	echo '<a href="?do=manage_pages&amp;del='.$del.'&amp;really=1">Ja</a> - ';
	echo '<a href="?do=manage_pages">Nein</a></p>';
}
if($del != null and $really == 1)
{
	mysql_query("DELETE FROM pages WHERE id = '".$del."'");
	echo '<p>Die Seite mit der ID '.$del.' wurde gelöscht.</p>';
}

$query = mysql_query("SELECT * FROM pages ORDER BY id");
echo '<table>';
while($row = mysql_fetch_object($query))
{
  echo '<tr><td>'.$row->id.'</td><td><a href="/?p='.$row->title.'">'.$row->fulltitle.'</a></td><td><a href="?do=edit_page&amp;id='.$row->id.'">bearbeiten</a></td><td><a href="?do=manage_pages&amp;del='.$row->id.'">x</a></td></tr>';
}
?>
</table>
<p><a href="?do=form">Neue Seite erstellen</a>