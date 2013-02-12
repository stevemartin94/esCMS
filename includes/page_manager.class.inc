<?php
    require_once('page.class.inc');
    require_once('database_exception.class.inc');

    class PageManager {
        private $mysqli;
        private $title_stmt;
        private $id_stmt;
        private $get_all_stmt;
        private $update_stmt;
        private $create_stmt;
        private $delete_stmt;

        function __construct(mysqli $mysqli) {
            $this->mysqli = $mysqli;
        }

        function getPageByTitle($title) {
            if (!$this->title_stmt) {
                $this->title_stmt = $this->mysqli->prepare("SELECT `id`, `title`, `fulltitle`, `content` FROM `pages` WHERE `title` = ?");
                if (!$this->title_stmt) {
                    throw new DatabaseException("Fehler bei Title Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

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
            if (!$this->id_stmt) {
                $this->id_stmt = $this->mysqli->prepare("SELECT `id`, `title`, `fulltitle`, `content` FROM `pages` WHERE `id` = ?");
                if (!$this->id_stmt) {
                    throw new DatabaseException("Fehler bei ID Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

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

        function updatePage($id, $fulltitle, $content) {
            if (!$this->update_stmt) {
                $this->update_stmt = $this->mysqli->prepare("UPDATE `pages` SET `fulltitle` = ?, `content` = ? WHERE `id` = ?");
                if (!$this->update_stmt) {
                    throw new DatabaseException("Fehler bei update Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }


            $this->update_stmt->bind_param("ssi", $fulltitle, $content, $id);
            if (!$this->update_stmt->execute()) {
                throw new DatabaseException("Fehler beim Bearbeiten der Seite: (".$this->update_stmt->errno.") ".$this->update_stmt->error);
            }
            $this->update_stmt->free_result();
        }

        function deletePage($id) {
            if (!$this->delete_stmt) {
                $this->delete_stmt = $this->mysqli->prepare("DELETE FROM `pages` WHERE `id` = ?");
                if (!$this->delete_stmt) {
                    throw new DatabaseException("Fehler bei delete Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $this->delete_stmt->bind_param("i", $id);
            if (!$this->delete_stmt->execute()) {
                throw new DatabaseException("Fehler beim Löschen der Seite: (".$this->delete_stmt->errno.") ".$this->delete_stmt->error);
            }
            $this->delete_stmt->free_result();
        }

        function createPage($title, $fulltitle, $content) {
            if (!$this->create_stmt) {
                $this->create_stmt = $this->mysqli->prepare("INSERT INTO `pages` (`title`, `fulltitle`, `content`) VALUES (?, ?, ?)");
                if (!$this->create_stmt) {
                    throw new DatabaseException("Fehler bei create Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $this->create_stmt->bind_param("sss", $title, $fulltitle, $content);
            if (!$this->create_stmt->execute()) {
                throw new DatabaseException("Fehler beim Erstellen der Seite: (".$this->create_stmt->errno.") ".$this->create_stmt->error);
            }
            $this->create_stmt->free_result();
        }

        function getAllPages() {
            if (!$this->get_all_stmt) {
                $this->get_all_stmt = $this->mysqli->prepare("SELECT `id`, `title`, `fulltitle`, `content` FROM `pages`");
                if (!$this->get_all_stmt) {
                    throw new DatabaseException("Fehler bei get all Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $this->get_all_stmt->bind_result($id, $title, $fulltitle, $content);
            if (!$this->get_all_stmt->execute()) {
                throw new DatabaseException("Fehler beim Holen der Seiten: (".$this->get_all_stmt->errno.") ".$this->get_all_stmt->error);
            }
            $pages = array();
            while ($this->get_all_stmt->fetch()) {
                $pages[] = new Page($id, $title, $fulltitle, $content);
            }
            $this->get_all_stmt->free_result();
            return $pages;
        }
    }
?>
