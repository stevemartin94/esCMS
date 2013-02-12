<?php
    require_once('database_exception.class.inc');
    require_once('user.class.inc');

    class UserManager {
        const LOGIN_ERROR_WRONG = -1;
        const LOGIN_ERROR_LOCKED = -2;

        private $mysqli;
        private $get_all_stmt;
        private $get_by_id_stmt;
        private $add_stmt;
        private $set_pass_stmt;
        private $delete_stmt;
        private $check_stmt;
        private $toggle_lock_stmt;

        function __construct($mysqli) {
            $this->mysqli = $mysqli;
        }

        function addUser($login, $password) {
            if (!$this->add_stmt) {
                $this->add_stmt = $this->mysqli->prepare("INSERT INTO `users` (`login`, `password`, `salt`) VALUES (?, SHA2(?, 256), ?)");
                if (!$this->add_stmt) {
                    throw new DatabaseException("Fehler bei add Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $salt = get_random_string(16);
            $saltedpass = $salt."::".$password;
            $this->add_stmt->bind_param("sss", $login, $saltedpass, $salt);
            if (!$this->add_stmt->execute()) {
                throw new DatabaseException("Fehler beim Hinzufügen des Benutzers: (".$this->add_stmt->errno.") ".$this->add_stmt->error);
            }
            $this->add_stmt->free_result();
        }

        function setUserPassword($id, $newpass) {
            if (!$this->set_pass_stmt) {
                $this->set_pass_stmt = $this->mysqli->prepare("UPDATE `users` SET `password` = SHA2(?, 256), `salt` = ? WHERE `id` = ?");
                if (!$this->set_pass_stmt) {
                    throw new DatabaseException("Fehler bei set pass Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $salt = get_random_string(16);
            $saltedpass = $salt."::".$newpass;
            $this->set_pass_stmt->bind_param("ssi", $saltedpass, $salt, $id);
            if (!$this->set_pass_stmt->execute()) {
                throw new DatabaseException("Fehler beim Setzen des Passworts: (".$this->set_pass_stmt->errno.") ".$this->set_pass_stmt->error);
            }
            $this->set_pass_stmt->free_result();
        }

        function setUserLogin($id, $newlogin) {
            if (!$this->set_login_stmt) {
                $this->set_login_stmt = $this->mysqli->prepare("UPDATE `users` SET `login` = ? WHERE `id` = ?");
                if (!$this->set_login_stmt) {
                    throw new DatabaseException("Fehler bei set login Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $this->set_login_stmt->bind_param("si", $newlogin, $id);
            if (!$this->set_login_stmt->execute()) {
                throw new DatabaseException("Fehler beim Setzen des Benutzernamens: (".$this->set_login_stmt->errno.") ".$this->set_login_stmt->error);
            }
            $this->set_login_stmt->free_result();
        }

        function toggleLock($id) {
            if (!$this->toggle_lock_stmt) {
                $this->toggle_lock_stmt = $this->mysqli->prepare("UPDATE `users` SET `locked` = NOT `locked` WHERE `id` = ?");
                if (!$this->toggle_lock_stmt) {
                    throw new DatabaseException("Fehler bei toggle lock Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $this->toggle_lock_stmt->bind_param("i", $id);
            if (!$this->toggle_lock_stmt->execute()) {
                throw new DatabaseException("Fehler beim Umschalten der Sperre: (".$this->toggle_lock_stmt->errno.") ".$this->toggle_lock_stmt->error);
            }
            $this->toggle_lock_stmt->free_result();
        }

        function deleteUserById($id) {
            if (!$this->delete_stmt) {
                $this->delete_stmt = $this->mysqli->prepare("DELETE FROM `users` WHERE `id` = ?");
                if (!$this->delete_stmt) {
                    throw new DatabaseException("Fehler bei delete Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $this->delete_stmt->bind_param("i", $id);
            if (!$this->delete_stmt->execute()) {
                throw new DatabaseException("Fehler beim Löschen des Benutzers: (".$this->delete_stmt->errno.") ".$this->delete_stmt->error);
            }
            $this->delete_stmt->free_result();
        }

        function getUserById($id) {
            if (!$this->get_by_id_stmt) {
                $this->get_by_id_stmt = $this->mysqli->prepare("SELECT `login`, `locked` FROM `users` WHERE `id` = ?");
                if (!$this->get_by_id_stmt) {
                    throw new DatabaseException("Fehler bei delete Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $this->get_by_id_stmt->bind_param("i", $id);
            $this->get_by_id_stmt->bind_result($login, $locked);
            if (!$this->get_by_id_stmt->execute()) {
                throw new DatabaseException("Fehler beim Holen des Users: (".$this->get_by_id_stmt->errno.") ".$this->get_by_id_stmt->error);
            }
            if (!$this->get_by_id_stmt->fetch()) {
                $this->get_by_id_stmt->free_result();
                return NULL;
            }
            $user = new User($id, $login, $locked > 0);
            $this->get_by_id_stmt->free_result();
            return $user;
        }

        function getAllUsers() {
            if (!$this->get_all_stmt) {
                $this->get_all_stmt = $this->mysqli->prepare("SELECT `id`, `login`, `locked` FROM `users` ORDER BY `id`");
                if (!$this->get_all_stmt) {
                    throw new DatabaseException("Fehler bei get all Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $this->get_all_stmt->bind_result($id, $login, $locked);
            if (!$this->get_all_stmt->execute()) {
                throw new DatabaseException("Fehler beim Holen der User: (".$this->get_all_stmt->errno.") ".$this->get_all_stmt->error);
            }
            $users = array();
            while ($this->get_all_stmt->fetch()) {
                $users[] = new User($id, $login, $locked > 0);
            }
            $this->get_all_stmt->free_result();
            return $users;
        }

        function checkLogin($login, $password) {
            if (!$this->check_stmt) {
                $this->check_stmt = $this->mysqli->prepare("SELECT `id`, `locked` FROM `users` WHERE `login` = ? AND `password` = SHA2(CONCAT(`salt`, '::', ?), 256)");
                if (!$this->check_stmt) {
                    throw new DatabaseException("Fehler bei check Stmt: (".$this->mysqli->errno.") ".$this->mysqli->error);
                }
            }

            $this->check_stmt->bind_param("ss", $login, $password);
            $this->check_stmt->bind_result($id, $locked);
            if (!$this->check_stmt->execute()) {
                throw new DatabaseException("Fehler beim Prüfen des Logins: (".$this->check_stmt->errno.") ".$this->check_stmt->error);
            }
            $users = array();
            if (!$this->check_stmt->fetch()) {
                $this->check_stmt->free_result();
                return UserManager::LOGIN_ERROR_WRONG;
            }
            $this->check_stmt->free_result();
            if ($locked > 0) {
                return UserManager::LOGIN_ERROR_LOCKED;
            }
            return $id;
        }
    }
?>
