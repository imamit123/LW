<?php
/**
 * @file
 * all_custom_block.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function all_custom_block_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['lw_custom-excelonz_free_trial_block'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'excelonz_free_trial_block',
    'module' => 'lw_custom',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['lw_custom-parent_menu'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'parent_menu',
    'module' => 'lw_custom',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'Parent' => 5,
    ),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'lw_theme',
        'weight' => -66,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['lw_genius_online-get_pricing_form_block'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'get_pricing_form_block',
    'module' => 'lw_genius_online',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['lw_genius_online-your_cart_status_block'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'your_cart_status_block',
    'module' => 'lw_genius_online',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['lw_genius_online_anonymous-anonymous_your_cart_status_block'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'anonymous_your_cart_status_block',
    'module' => 'lw_genius_online_anonymous',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['lw_genius_online_anonymous-get_pricing_form_block_anonymous'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'get_pricing_form_block_anonymous',
    'module' => 'lw_genius_online_anonymous',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['lw_parent_assignment-create_parent_assignment'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'create_parent_assignment',
    'module' => 'lw_parent_assignment',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['lw_parent_assignment-detail_assignment_worksheet'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'detail_assignment_worksheet',
    'module' => 'lw_parent_assignment',
    'node_types' => array(),
    'pages' => 'parent/view/assignment/worksheet/*',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['lw_parent_assignment-menu_tabs_parent_login'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'menu_tabs_parent_login',
    'module' => 'lw_parent_assignment',
    'node_types' => array(),
    'pages' => 'parent/assignment/*/*
parent/assignment/view/*/*
parent/assignments/list/view/*/*',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => 'highlighted',
        'status' => 1,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['lw_parent_assignment-parent_detail_assignment_view'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'parent_detail_assignment_view',
    'module' => 'lw_parent_assignment',
    'node_types' => array(),
    'pages' => 'parent/assignments/view/*',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['lw_parent_assignment-sort_by'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'sort_by',
    'module' => 'lw_parent_assignment',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['lw_parent_assignment-view_parent_assignment'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'view_parent_assignment',
    'module' => 'lw_parent_assignment',
    'node_types' => array(),
    'pages' => 'parent/assignments/list/view/*',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['lw_report-parent_subject_topic_table'] = array(
    'cache' => 1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'parent_subject_topic_table',
    'module' => 'lw_report',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['lw_worksheet-explore_subject_topic_for_class'] = array(
    'cache' => -1,
    'css_class' => 'page_topic_subject',
    'custom' => 0,
    'delta' => 'explore_subject_topic_for_class',
    'module' => 'lw_worksheet',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['lw_worksheet-homepage_subject_practice'] = array(
    'cache' => -1,
    'css_class' => 'background-green',
    'custom' => 0,
    'delta' => 'homepage_subject_practice',
    'module' => 'lw_worksheet',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['lw_worksheet-inner_page_header_menu'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'inner_page_header_menu',
    'module' => 'lw_worksheet',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => 'menu_bar',
        'status' => 1,
        'theme' => 'lw_theme',
        'weight' => -78,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['lw_worksheet-try_question_and_worksheet'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'try_question_and_worksheet',
    'module' => 'lw_worksheet',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['panels_mini-inner_class_page'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'inner_class_page',
    'module' => 'panels_mini',
    'node_types' => array(),
    'pages' => 'class/*',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['panels_mini-pricing_page_block_display'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'pricing_page_block_display',
    'module' => 'panels_mini',
    'node_types' => array(),
    'pages' => 'pricingplans/form/*
pricingplans',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['views-069b58bc316a92d93a5d7fc6105508eb'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => '069b58bc316a92d93a5d7fc6105508eb',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'lw_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-55d88040c255c6af45be1418acf41f9c'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => '55d88040c255c6af45be1418acf41f9c',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'front
<front>',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'lw_theme',
        'weight' => -67,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['views-6f40d8ea86dd6f0ee2e5079d229a7308'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => '6f40d8ea86dd6f0ee2e5079d229a7308',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'dossier' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'dossier',
        'weight' => 0,
      ),
      'lw_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'lw_theme',
        'weight' => -42,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
