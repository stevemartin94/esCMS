<?php
session_start();
?>
<!DOCTYPE HTML>
<html>
<head>
<meta charset="UTF-8">
<title>Admin Control Panel</title>
<link rel="stylesheet" type="text/css" href="styles/acp.css" />
</head>

<body>
<?php
require_once('../includes/config.inc');
require_once('../includes/util.inc');
require_once('../includes/user_manager.class.inc');


$login_form = <<<EOS
<form action="index.php" method="post">
    <table>
        <tr>
            <td>User:</td>
            <td><input type="text" name="login" /></td>
        </tr>
        <tr>
            <td>Passwort:</td>
            <td><input type="password" name="password" /></td>
        </tr>
    </table>
    <input type="hidden" name="action" value="login" />
    <input type="submit" value="Login" />
</form>

EOS;

$navigation = <<<EOS
<nav>
<a href="?do=manage_pages">Seiten verwalten</a>
<a href="?do=manage_navigation">Navigation verwalten</a>
<a href="?do=manage_users">Benutzer verwalten</a>
</nav>

EOS;

$mysqli = new mysqli($config['db_host'], $config['db_user'], $config['db_pass'], $config['db_dbname']);

$mysqli->set_charset("utf8");

if ($mysqli->connect_error) {
    echo("Fehler bei der Datenbankverbindung: (".$mysqli->connect_errno.") ".$mysqli->connect_error);
}

if (get_postvar('action') == "login") {
    $login = get_postvar('login');
    $password = get_postvar('password');
    try {
        $user_mgr = new UserManager($mysqli);
        $result = $user_mgr->checkLogin($login, $password);
        if ($result >= 0) {
            $_SESSION['user_id'] = $result;
        } else {
            echo '<span style="color:red">';
            switch ($result) {
                case UserManager::LOGIN_ERROR_WRONG:
                    echo "Benutzername oder Passwort falsch";
                    break;
                case UserManager::LOGIN_ERROR_LOCKED:
                    echo "Benutzer ist gesperrt";
                    break;
                default:
                    echo "Unbekannter Fehler";
                    break;
            }
            echo '</span>';
        }
    } catch (DatabaseException $ex) {
        echo($ex->getMessage());
    }
}

if (!isset($_SESSION['user_id']) || $_SESSION['user_id'] === NULL) {
    echo($login_form);
} else {
    echo $navigation;

    $do = get_getvar('do');
    if($do && preg_match("/[A-Za-z0-9-_]+/", $do) && file_exists("do/".$do.".inc")) {
        define('ESCMS_ACP', NULL);
        require("do/".$do.".inc");
    } else {
        echo "Admin Control Panel. Bitte wählen Sie eine Option aus dem Menü oben.";
    }
}

$mysqli->close();
?>
</body>
</html>
