<?php
    require_once('navigation_entry.class.inc');
    require_once('database_exception.class.inc');

    class NavigationManager {
        private $mysqli;
        private $get_all_stmt;
        private $update_stmt;
        private $create_stmt;
        private $delete_stmt;
        private $id_stmt;

        function __construct(mysqli $mysqli) {
            $this->mysqli = $mysqli;
        }

        function updateEntry($id, $title, $url) {
            if (!$this->update_stmt) {
                $this->update_stmt = $this->mysqli->prepare("UPDATE `navigation` SET `title` = ?, `url` = ? WHERE `id` = ?");
                if (!$this->update_stmt) {
                    throw new DatabaseException("Fehler bei update Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }


            $this->update_stmt->bind_param("ssi", $title, $url, $id);
            if (!$this->update_stmt->execute()) {
                throw new DatabaseException("Fehler beim Bearbeiten des Navigationseintrags: (".$this->update_stmt->errno.") ".$this->update_stmt->error);
            }
            $this->update_stmt->free_result();
        }

        function deleteEntry($id) {
            if (!$this->delete_stmt) {
                $this->delete_stmt = $this->mysqli->prepare("DELETE FROM `navigation` WHERE `id` = ?");
                if (!$this->delete_stmt) {
                    throw new DatabaseException("Fehler bei delete Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $this->delete_stmt->bind_param("i", $id);
            if (!$this->delete_stmt->execute()) {
                throw new DatabaseException("Fehler beim Löschen des Navigationseintrags: (".$this->delete_stmt->errno.") ".$this->delete_stmt->error);
            }
            $this->delete_stmt->free_result();
        }

        function createEntry($title, $url) {
            if (!$this->create_stmt) {
                $this->create_stmt = $this->mysqli->prepare("INSERT INTO `navigation` (`title`, `url`) VALUES (?, ?)");
                if (!$this->create_stmt) {
                    throw new DatabaseException("Fehler bei create Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $this->create_stmt->bind_param("ss", $title, $url);
            if (!$this->create_stmt->execute()) {
                throw new DatabaseException("Fehler beim Erstellen des Navigationseintrags: (".$this->create_stmt->errno.") ".$this->create_stmt->error);
            }
            $this->create_stmt->free_result();
        }

        function getEntryById($id) {
            if (!$this->id_stmt) {
                $this->id_stmt = $this->mysqli->prepare("SELECT `id`, `title`, `url` FROM `navigation` WHERE `id` = ?");
                if (!$this->id_stmt) {
                    throw new DatabaseException("Fehler bei ID Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $this->id_stmt->bind_param("i", $id);
            $this->id_stmt->bind_result($id, $title, $url);
            if (!$this->id_stmt->execute()) {
                throw new DatabaseException("Fehler beim Laden des Navigationseintrags: (".$this->id_stmt->errno.") ".$this->id_stmt->error);
            }
            if (!$this->id_stmt->fetch()) {
                return NULL;
            }
            $this->id_stmt->free_result();
            return new NavigationEntry($id, $title, $url);
        }

        function getAllEntries() {
            if (!$this->get_all_stmt) {
                $this->get_all_stmt = $this->mysqli->prepare("SELECT `id`, `title`, `url` FROM `navigation`");
                if (!$this->get_all_stmt) {
                    throw new DatabaseException("Fehler bei get all Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $this->get_all_stmt->bind_result($id, $title, $url);
            if (!$this->get_all_stmt->execute()) {
                throw new DatabaseException("Fehler beim Holen der Navigationseinträge: (".$this->get_all_stmt->errno.") ".$this->get_all_stmt->error);
            }
            $entries = array();
            while ($this->get_all_stmt->fetch()) {
                $entries[] = new NavigationEntry($id, $title, $url);
            }
            $this->get_all_stmt->free_result();
            return $entries;
        }
    }
?>
