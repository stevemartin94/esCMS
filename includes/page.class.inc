<?php
    class Page {
        public $id;
        public $title;
        public $fulltitle;
        public $content;

        function __construct($id, $title, $fulltitle, $content) {
            $this->id = $id;
            $this->title = $title;
            $this->fulltitle = $fulltitle;
            $this->content = $content;
        }
    }
?>