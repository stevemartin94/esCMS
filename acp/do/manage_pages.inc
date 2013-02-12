<?php
if (!defined('ESCMS_ACP')) {
    die();
}
?>
<h1>Seiten verwalten</h1>
<?php
require_once('../includes/page_manager.class.inc');
require_once('../includes/util.inc');

$page_mgr = new PageManager($mysqli);

$action = get_getvar('action');

$id = get_getvar('id');

if ($action == 'delete') {
    if (is_numeric($id)) {
        $id = (int)$id;
        $really = get_getvar('really');
        if ($id and $really != 1)
        {
            echo '<p>Seite mit der ID '.$id.' wirklich löschen?<br />';
            echo '<a href="?do=manage_pages&amp;action=delete&amp;id='.$id.'&amp;really=1">Ja</a> - ';
            echo '<a href="?do=manage_pages">Nein</a></p>';
        } elseif ($id and $really == 1) {
            try {
                $page_mgr->deletePage($id);
                echo '<p>Die Seite mit der ID '.$id.' wurde gelöscht.</p>';
            } catch (DatabaseException $ex) {
                echo $ex->getMessage();
            }
        }
    } else {
        echo "ID muss numerisch sein!";
    }
} elseif ($action == 'create') {
    $fulltitle = get_postvar('fulltitle');
    $content = get_postvar('content');
    $title = trim(strtolower(preg_replace("/[^\w]+/", "-", $fulltitle)));
    $page_mgr = new PageManager($mysqli);
    try {
        $page_mgr->createPage($title, $fulltitle, $content);
        echo "Seite ".htmlspecialchars($_POST['fulltitle'])." wurde erstellt.<br />";
    } catch (DatabaseException $ex) {
        echo $ex->getMessage();
    }
} elseif ($action == 'edit') {
    $fulltitle = get_postvar('fulltitle');
    $content = get_postvar('content');
    if ($id !== NULL && $content !== NULL && $fulltitle !== NULL)
    {
        try {
            $page_mgr->updatePage($id, $fulltitle, $content);
            echo 'Seite wurde bearbeitet.<br />';
        } catch (DatabaseException $ex) {
            echo $ex->getMessage();
        }
    }
}

$pages = $page_mgr->getAllPages();
echo '<table>';
foreach ($pages as $page)
{
    echo '<tr><td>'.$page->id.'</td><td><a href="../?p='.$page->title.'">'.$page->fulltitle.'</a></td><td><a href="?do=edit_page&amp;id='.$page->id.'"><img src="img/pencil.png" /></a></td><td><a href="?do=manage_pages&amp;action=delete&amp;id='.$page->id.'"><img src="img/delete.png" /></a></td></tr>';
}

echo '</table>';
if ($action != 'add') {
    echo '<p><a href="?do=edit_page"><img src="img/add.png" /> Neue Seite erstellen</a></p>';
}
?>