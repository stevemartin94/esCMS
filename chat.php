<?php
require('includes/mysql_connect.inc');
mysql_select_db("usr_web4_5",$con);
$abfrage = "SELECT * FROM chat ORDER BY id DESC";
$ergebnis = mysql_query($abfrage,$con);
while($name = mysql_fetch_array($ergebnis))
{	
	echo '
	
				<table border ="1" cellspacing="4">
				  <tr>
					<td width="100">'.$name['name'].':</td>
					<td width="300">'.$name['text'].'</td>
				  </tr>
				</table>
				
			';
}

mysql_close($con);
?>