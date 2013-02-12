<?php
if (!defined('ESCMS_ACP')) {
    die();
}
?>
<h1>Benutzer verwalten</h1>
<?php
require_once("../includes/user_manager.class.inc");

$action = get_getvar('action');
$id = get_getvar('id');

$user_mgr = new UserManager($mysqli);

if ($action == 'add')
{
    $username = get_postvar('username');
    $password = get_postvar('password');
    if($username and $password)
    {
        try {
            $user_mgr->addUser($username, $password);
            echo "Benutzer ".htmlspecialchars($username)." wurde erstellt.<br />";
        } catch (DatabaseException $ex) {
            echo $ex->getMessage();
        }
    } else {
        echo 'Bitte alle Felder ausfüllen!';
    }
    echo '
    <form method="post" action="">
    Benutzername: <input type="text" name="username" size="50" /><br />
    Passwort: <input type="password" name="password" size="50" /><br />
    <input type="submit" name="absenden" value="Absenden" />
    </form>
    ';
} elseif ($action == 'edit') {
    echo '<h2>Benutzer bearbeiten</h2>';

    $username = get_postvar('username');
    $password = get_postvar('password');

    if ($username) {
        try {
            $user_mgr->setUserLogin($id, $username);
            echo '<p>Benutzername wurde gesetzt.</p>';
        } catch (DatabaseException $ex) {
            echo '<div class="error">'.$ex->getMessage().'</div>';
        }
        
    }

    if ($password) {
        try {
            $user_mgr->setUserPassword($id, $password);
            echo '<p>Passwort wurde gesetzt.</p>';
        } catch (DatabaseException $ex) {
            echo '<div class="error">'.$ex->getMessage().'</div>';
        }
    }

    $user = $user_mgr->getUserById($id);

    echo '
    <form method="post" action="">
    Benutzername: <input type="text" name="username" size="50" value="'.htmlspecialchars($user->login).'" /><br />
    Passwort: <input type="password" name="password" size="50" /><br />
    <input type="submit" name="absenden" value="Absenden" />
    </form>
    ';
} elseif ($action == "toggle_lock") {
    $p_id = get_postvar('id');
    $user_mgr->toggleLock($p_id);
}

//delete
$del = get_getvar('del');
$really = get_getvar('really');

if (is_numeric($del)) {
    if ($del != NULL and $really != 1)
    {
        echo '<p>Benutzer mit der ID '.$del.' wirklich löschen?<br />';
        echo '<a href="?do=manage_users&amp;del='.$del.'&amp;really=1">Ja</a> - ';
        echo '<a href="?do=manage_users">Nein</a></p>';
    } elseif ($del != NULL and $really == 1)
    {
        if (is_numeric($del)) {
            $user_mgr->deleteUserById($del);
            echo '<p>Der Benutzer mit der ID '.$del.' wurde gelöscht.</p>';
        } else {
            echo '<p>Die ID muss numerisch sein.</p>';
        }
    }
}

$users = $user_mgr->getAllUsers();
echo '<table>';
echo '<thead><tr><th>ID</th><th>Name</th></thead>';
foreach ($users as $user)
{
    $filename = "lock" . (($user->locked) ? "" : "_open") . ".png";
    echo '<tr><td>'.$user->id.'</td><td>'.htmlspecialchars($user->login).'</td><td style="text-align: center"><a href="?do=manage_users&amp;action=edit&amp;id='.$user->id.'"><img src="img/pencil.png" /></a></td><td style="text-align: center"><a href="?do=manage_users&amp;del='.$user->id.'"><img src="img/delete.png" /></a></td><td style="text-align: center"><form action="?do=manage_users&amp;action=toggle_lock" method="post"><input type="image" src="img/'.$filename.'" /><input type="hidden" name="id" value="'.$user->id.'" /></form></td></tr>';
}
echo '</table>';

if ($action != 'add')
{
    echo '<p><a href="?do=manage_users&amp;action=add"><img src="img/add.png" /> Neuen Benutzer erstellen</a></p>';
}
?>