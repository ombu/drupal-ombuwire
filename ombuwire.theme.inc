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
      <label id="ombuwire-regions-label"><input type="checkbox" /> Highlight Regions</label>
    </div>
  </div>
</div>
HEREDOC;
}

function _ombuwire_sidebar_menu($tree) {
  $items = array();
  $active_path = isset($_REQUEST['q']) ? $_REQUEST['q'] : '';
  $active_root_path = ombuwire_active_root_path();
  foreach ($tree as $url => $arr) {

    if (array_key_exists('#markup', $arr)) {
      $items[] = '<li>'. $arr['#markup'] .'</li>';
      continue;
    }

    // Main link
    $options = array(
      'attributes' => array(
        'class' => ($url === $active_path) ? array('active') : '',
      )
    );
    $item = '<div class="root">'. l($arr['#title'], $url, $options) .'</div>';

    // wireframe, design, static links
    $displays = array();
    foreach ($arr as $key => $val) {
      if (stristr($key, '#') === FALSE) {
        if ($url === '<front>') {
          $display_url = $key;
        }
        else {
          $display_url = $url.'/'.$key;
        }

        $display_class = ($display_url === $active_path) ? 'active' : '';
        $displays[] = '<a href="'.base_path() . $display_url.'" class="'.$display_class.'">'.ucwords($key).'</a>';
      }
    }
    if (!empty($displays)) {
      $item .= '<div class="displays">&nbsp;&lfloor; '. implode(' &middot; ', $displays) .'</div>';
    }

    // children
    if (!empty($arr['#children'])) {
      $item .= _ombuwire_sidebar_menu($arr['#children']);
    }

    $class = '';
    if (!$active_root_path && $url === '<front>') {
      $class = 'active';
    }
    elseif ($url === $active_root_path) {
      $class = 'active';
    }
    $icon = _ombuwire_sidebar_menu_icon($arr['#status']);
    $items[] = '<li class="'. $class .' has-icon">'. $icon . $item .'</li>';
  }

  return '<ul>'. implode($items) .'</ul>';
}

function _ombuwire_sidebar_menu_icon($status) {
  $human_name = ucwords(str_replace('-', ' ', $status));
  return "<a class='icon icon-$status noclick' title='$human_name' href='#'></a>";
}
