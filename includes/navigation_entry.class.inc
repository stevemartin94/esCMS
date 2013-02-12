<?php
    class NavigationEntry {
        public $id;
        public $title;
        public $url;

        function __construct($id, $title, $url) {
            $this->id = $id;
            $this->title = $title;
            $this->url = $url;
        }
    }
?>
