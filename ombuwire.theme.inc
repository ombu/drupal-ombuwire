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
  foreach ($tree as $url => $arr) {

    // Main link
    $item = l($arr['#title'], $url);

    // wireframe, design, static links
    $variations = array();
    foreach ($arr as $key => $val) {
      if (stristr($key, '#') === FALSE) {
        $variations[] = l(ucwords($key), $url.'/'.$key);
      }
    }
    $item .= '<div class="small">'. implode(' - ', $variations) .'</div>';

    // children
    if (!empty($arr['#children'])) {
      $item .= _ombuwire_sidebar_menu($arr['#children']);
    }

    $items[] = '<li class="'.$arr['#status'].'">'. $item .'</li>';
  }

  return '<ul>'. implode($items) .'</ul>';
}