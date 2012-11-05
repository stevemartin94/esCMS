<!DOCTYPE HTML>
<html>
<head>
<meta charset="UTF-8">
<title>Admin Control Panel</title>
<link rel="stylesheet" type="text/css" href="styles/acp.css" />
</head>

<body>
<nav>
<a href="?do=manage_pages">Seiten verwalten</a>
<a href="?do=manage_navigation">Navigation verwalten</a>
<a href="?do=manage_users">Benutzer verwalten</a>

</nav>

<?php
$do = $_GET['do'];

if(file_exists("do/".$do.".php"))
{
require("do/".$do.".php");
}
?>
</body>
</html>