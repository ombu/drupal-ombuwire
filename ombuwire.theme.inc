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
  drupal_add_library('ombuwire', 'ombuwire');
  $tree = ombuwire_get_sitemap();
  $menu = _ombuwire_sidebar_menu($tree);
	return <<<HEREDOC
<div id="ombuwire-sidebar">
  <a href="#" class="opener" title="Open Wireframe/Design Menu">&equiv;</a>
  <div class="cloak">
    <div class="ombuwire-menu">
      <a href="#" class="closer" title="Close Wireframe/Design Menu">&otimes;</a>
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

    if (strpos($url, '#') === 0) {
      if ($url === '#markup') {
        $items[] = '<li>'. $arr .'</li>';
      }
      continue;
    }

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
    $icon = _ombuwire_sidebar_menu_icon($arr['#status']);
    $items[] = '<li class="'. $class .' has-icon">'. $icon . $item .'</li>';
  }

  return '<ul>'. implode($items) .'</ul>';
}

function _ombuwire_sidebar_menu_icon($status) {
  $human_name = ucwords(str_replace('-', ' ', $status));
  return "<a class='icon icon-$status noclick' title='$human_name' href='#'></a>";
}