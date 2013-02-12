<?php
if (!defined('ESCMS_ACP')) {
    die();
}

require_once('../includes/util.inc');
require_once('../includes/page_manager.class.inc');

$id = get_getvar('id');

$page = NULL;

if (is_numeric($id)) {
    $page_mgr = new PageManager($mysqli);
    $page = $page_mgr->getPageById($id);
} else {
    $id = '';
}
?>

<script type="text/javascript" src="js/tiny_mce/tiny_mce.js"></script>
<script type="text/javascript">
tinyMCE.init({
    theme : "advanced",
    mode : "textareas",
    entity_encoding : "raw",
    plugins : "advhr,advlink,advlist,autolink,autoresize,contextmenu,directionality,fullscreen,inlinepopups,media,nonbreaking,paste,print,searchreplace,style,table",
    theme_advanced_buttons1 : "newdocument,|,undo,redo,|,bold,italic,underline,strikethrough,|,justifyleft,justifycenter,justifyright,justifyfull,|,styleselect,formatselect,fontselect,fontsizeselect,help",
    theme_advanced_buttons2 : "cut,copy,paste,pastetext,pasteword,|,search,replace,|,bullist,numlist,|,outdent,indent,blockquote,|,link,unlink,anchor,image,cleanup,code,|,forecolor,backcolor",
    theme_advanced_buttons3 : "tablecontrols,|,hr,removeformat,visualaid,|,sub,sup,|,charmap,media,advhr,|,print,|,ltr,rtl,|,fullscreen",
    theme_advanced_buttons4 : "styleprops,|,nonbreaking"
});
</script>

<h1>Seite <?php echo((is_object($page)) ? "bearbeiten" : "erstellen"); ?></h1>
<form method="post" action="?do=manage_pages&amp;action=<?php echo((is_object($page)) ? "edit" : "create") ?>">
<table>
<tr>
<td>
Seitentitel:
</td>
<td>
<input type="text" name="fulltitle" size="50" value="<?php echo((is_object($page)) ? htmlspecialchars($page->fulltitle) : "") ?>" />
</td>
</tr>
<tr>
<td colspan="2">
Inhalt:
</td>
</tr>
<tr>
<td colspan="2">
<textarea name="content" style="width: 900px" rows="20"><?php echo((is_object($page)) ? htmlspecialchars($page->content) : "") ?></textarea>
</td>
</tr>
</table>
<input type="hidden" name="id" value="<?php echo $id ?>" />
<input type="submit" name="absenden" value="Absenden" />
</form>
<p><a href="?do=manage_pages">Zurück zur Seitenverwaltung</a></p>