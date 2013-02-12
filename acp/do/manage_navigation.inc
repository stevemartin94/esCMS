<?php
if (!defined('ESCMS_ACP')) {
    die();
}
?>
<h1>Navigation verwalten</h1>
<?php
require_once("../includes/navigation_manager.class.inc");
require_once("../includes/util.inc");

$nav_mgr = new NavigationManager($mysqli);

$action = get_getvar('action');
$id = get_getvar('id');
$really = get_getvar('really');

if ($action == 'add') {
    $title = get_postvar('title');
    $url = get_postvar('url');
    if ($title !== NULL and $url !== NULL) {
        $nav_mgr->createEntry($title, $url);
        echo 'Link '.htmlspecialchars($title).' wurde erstellt.<br />';
    }
    echo '
    <form method="post" action="">
    Titel: <input type="text" name="title" size="50" /><br />
    URL: <input type="text" name="url" size="50" /><br />
    <input type="submit" name="absenden" value="Absenden" />
    </form>
    ';
} elseif ($action == 'edit') {
    $title = get_postvar('title');
    $url = get_postvar('url');
    if (is_numeric($id)) {
        if ($id !==NULL and $title !== NULL and $url !== NULL) {
            $title = get_postvar('title');
            $url = get_postvar('url');
            $nav_mgr->updateEntry($id, $title, $url);
        } else {
            $entry = $nav_mgr->getEntryById($id);
            echo '
            <h1>Link bearbeiten</h1>
            <form method="post" action="">
            Titel: <input type="text" name="title" size="50" value="'.htmlspecialchars($entry->title).'" /><br />
            URL: <input type="text" name="url" size="50" value="'.htmlspecialchars($entry->url).'" /><br />
            <input type="submit" name="absenden" value="Absenden" />
            </form>
            ';
        }
    } else {
        echo "<p>Die ID muss numerisch sein!</p>";
    }
} elseif ($action == 'delete') {
    if (is_numeric($id)) {
        if ($id !== NULL and $really != 1) {
            echo '<p>Link mit der ID '.$id.' wirklich löschen?<br />';
            echo '<a href="?do=manage_navigation&amp;action=delete&amp;id='.$id.'&amp;really=1">Ja</a> - ';
            echo '<a href="?do=manage_navigation">Nein</a></p>';
        } elseif ($id !== NULL and $really == 1) {
            $nav_mgr->deleteEntry($id);
            echo '<p>Der Link mit der ID '.$id.' wurde gelöscht.</p>';
        }
    } else {
        echo "<p>Die ID muss numerisch sein!</p>";
    }
}

$entries = $nav_mgr->getAllEntries();
echo '<table>';
echo '<tr><th>ID</th><th>Titel</th></tr>';
foreach ($entries as $entry) {
    echo '<tr><td>'.$entry->id.'</td><td><a href="../?p='.htmlspecialchars($entry->url).'">'.htmlspecialchars($entry->title).'</a></td><td><a href="?do=manage_navigation&amp;action=edit&amp;id='.$entry->id.'"><img src="img/pencil.png" /></a></td><td><a href="?do=manage_navigation&amp;action=delete&amp;id='.$entry->id.'"><img src="img/delete.png" /></a></td></tr>';
}
echo '</table>';

if($action != 'add') {
    echo '
    <p><a href="?do=manage_navigation&amp;action=add"><img src="img/add.png" /> Neuen Link erstellen</a></p>
    ';
}
?>
