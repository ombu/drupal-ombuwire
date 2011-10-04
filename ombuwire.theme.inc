<?php

function theme_ombuwire_page_wireframe($vars) {
	return theme('ombuwire_page_image', array('url' => $vars['url']));
}

function theme_ombuwire_page_design($vars) {
	return theme('ombuwire_page_image', array('url' => $vars['url']));
}

function theme_ombuwire_page_image($vars) {
	return "<img class='ombuwire-center' src='{$vars['url']}' />";
}

function theme_ombuwire_page_static($vars) {
	return "<iframe class='ombuwire-iframe' src='{$vars['url']}'></iframe>";
}

function theme_ombuwire_sidebar($vars) {
	return "<div id='ombuwire-sidebar'>SIDEBAR</div>";
}
