<ul>
	<?php
	require("includes/mysql_connect.inc");
	mysql_select_db("usr_web4_5", $con);
	
	$query = mysql_query("SELECT * FROM navigation ORDER BY id");
	while($row = mysql_fetch_object($query))
	{
     	if($p == $row->url)
     	{
           	echo '<li class="current">';
     	}
     	else
     	{
           	echo '<li>';
     	}
		echo '<a href="/?p='.$row->url.'">'.$row->title.'</a></li>';
	}
	?>
</ul>