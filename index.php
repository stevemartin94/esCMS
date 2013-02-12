<?php
require_once("includes/config.inc");
require_once("includes/util.inc");
require_once("includes/page_manager.class.inc");

$mysqli = new mysqli($config['db_host'], $config['db_user'], $config['db_pass'], $config['db_dbname']);

$mysqli->set_charset("utf8");

$pagemgr = new PageManager($mysqli);

if (!$mysqli->connect_error) {
    try {
        if (isset($_GET['p']) && is_string($_GET['p'])) {
            $page = $pagemgr->getPageByTitle($_GET['p']);
        } elseif (isset($_GET['id']) && is_string($_GET['id'])) {
            $page = $pagemgr->getPageByID($_GET['id']);
        } else {
            $page = $pagemgr->getPageByTitle('index');
        }

        if (!$page) {
            $page = $pagemgr->getPageByTitle('404');
        }
    } catch (DatabaseException $ex) {
        echo($ex->getMessage());
    }
} else {
    echo("Fehler bei Datenbankverbindung: (".$mysqli->connect_errno.") ".$mysqli->connect_error);
}

require("includes/header.inc");

    echo '<h1>'.$page->fulltitle.'</h1>';
    echo $page->content;

require("includes/footer.inc");

$mysqli->close();
?>