<?php

function theme_ombuwire_page_wireframe($vars) {
	return theme('ombuwire_page_image', array('url' => $vars['url']));
}

function theme_ombuwire_page_design($vars) {
	return theme('ombuwire_page_image', array('url' => $vars['url']));
}

function theme_ombuwire_page_image($vars) {
  $urls = is_array($vars['url']) ? $vars['url'] : array($vars['url']);
  $out = '';
  foreach ($urls as $url) {
    $out .= "<img class='ombuwire-center' src='$url' />";
  }
	return $out;
}

function theme_ombuwire_page_static($vars) {
	return "<iframe class='ombuwire-iframe' src='{$vars['url']}'></iframe>";
}

function theme_ombuwire_sidebar($vars) {
  $tree = ombuwire_get_sitemap();
  $menu = _ombuwire_sidebar_menu($tree);
	return <<<HEREDOC
<div id="ombuwire-sidebar">
  <a href="#" class="opener" title="Wireframe/Design Menu">&equiv;</a>
  <div class="cloak">
    <div class="ombuwire-menu">
      $menu
    </div>
  </div>
</div>
HEREDOC;
}

function _ombuwire_sidebar_menu($tree) {
  $items = array();
  $active_path = drupal_get_path_alias(current_path());
  $active_root_path = ombuwire_active_root_path();
  foreach ($tree as $url => $arr) {

    // Main link
    $item = '<div class="root">'. l($arr['#title'], $url) .'</div>';

    // wireframe, design, static links
    $displays = array();
    foreach ($arr as $key => $val) {
      if (stristr($key, '#') === FALSE) {
        $displays[] = l(ucwords($key), $url.'/'.$key);
      }
    }
    if (!empty($displays)) {
      $item .= '<div class="displays">&nbsp;&lfloor; '. implode(' &middot; ', $displays) .'</div>';
    }

    // children
    if (!empty($arr['#children'])) {
      $item .= _ombuwire_sidebar_menu($arr['#children']);
    }

    $class = ($url === $active_root_path) ? 'active' : '';
    $class .= ' '. $arr['#status'];
    $items[] = '<li class="'. $class .'">'. $item .'</li>';
  }

  return '<ul>'. implode($items) .'</ul>';
}