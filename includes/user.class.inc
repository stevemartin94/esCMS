<?php
    class User {
        public $id;
        public $login;
        public $locked;

        function __construct($id, $login, $locked) {
            $this->id = $id;
            $this->login = $login;
            $this->locked = $locked;
        }
    }
?>
