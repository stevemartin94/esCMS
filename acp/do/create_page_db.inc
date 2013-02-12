<?php

$fulltitle = get_postvar('fulltitle');
$content = get_postvar('content');
$title = trim(strtolower(preg_replace("/[^\w]+/", "-", $fulltitle)));
$page_mgr = new PageManager($mysqli);
$page_mgr->createPage($title, $fulltitle, $content);
?>

Seite <?php echo htmlspecialchars($_POST['fulltitle']) ?> wurde erstellt.<br />
<a href="/?p=<? echo $title ?>">Seite ansehen</a>
<p><a href="?do=manage_pages">Zurück zur Seitenverwaltung</a></p>