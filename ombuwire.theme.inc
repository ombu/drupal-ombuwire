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
  $tree = ombuwire_get_sitemap();
  $menu = _ombuwire_sidebar_menu($tree);
	return '<div id="ombuwire-sidebar">'. $menu .'</div>';
}

function _ombuwire_sidebar_menu($tree) {
  $items = array();
  $active_path = drupal_get_path_alias(current_path());
  $active_root_path = ombuwire_active_root_path();
  foreach ($tree as $url => $arr) {

    // Main link
    $item = '<div class="root '.$arr['#status'].'">'. l($arr['#title'], $url) .'</div>';

    // wireframe, design, static links
    $displays = array();
    foreach ($arr as $key => $val) {
      if (stristr($key, '#') === FALSE) {
        $displays[] = l(ucwords($key), $url.'/'.$key);
      }
    }
    $item .= '<div class="displays">&nbsp;&lfloor; '. implode(' &middot; ', $displays) .'</div>';

    // children
    if (!empty($arr['#children'])) {
      $item .= _ombuwire_sidebar_menu($arr['#children']);
    }

    $class = ($url === $active_root_path) ? 'active' : '';

    $items[] = '<li class="'. $class .'">'. $item .'</li>';
  }

  return '<ul>'. implode($items) .'</ul>';
}