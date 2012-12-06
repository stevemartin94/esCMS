<?php
    require_once('page.class.inc');
    require_once('database_exception.class.inc');

    class PageManager {
        private $mysqli;
        private $title_stmt;
        private $id_stmt;

        function __construct($mysqli) {
            $this->mysqli = $mysqli;

            $this->title_stmt = $this->mysqli->prepare("SELECT id, title, fulltitle, content FROM `pages` WHERE `title` = ?");
            if (!$this->title_stmt) {
                throw new DatabaseException("Fehler bei Title Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
            }

            $this->id_stmt = $this->mysqli->prepare("SELECT id, title, fulltitle, content FROM `pages` WHERE `id` = ?");
            if (!$this->id_stmt) {
                throw new DatabaseException("Fehler bei ID Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
            }
        }

        function getPageByTitle($title) {
            $this->title_stmt->bind_param("s", $title);
            $this->title_stmt->bind_result($id, $title, $fulltitle, $content);
            if (!$this->title_stmt->execute()) {
                throw new DatabaseException("Fehler beim Laden der Seite: (".$this->title_stmt->errno.") ".$this->title_stmt->error);
            }
            if (!$this->title_stmt->fetch()) {
                return NULL;
            }
            $this->title_stmt->free_result();
            return new Page($id, $title, $fulltitle, $content);
        }

        function getPageByID($id) {
            $this->id_stmt->bind_param("i", $id);
            $this->id_stmt->bind_result($id, $title, $fulltitle, $content);
            if (!$this->id_stmt->execute()) {
                throw new DatabaseException("Fehler beim Laden der Seite: (".$this->id_stmt->errno.") ".$this->id_stmt->error);
            }
            if (!$this->id_stmt->fetch()) {
                return NULL;
            }
            $this->id_stmt->free_result();
            return new Page($id, $title, $fulltitle, $content);
        }
    }
?>
