<?php
/**
 * @file
 * lw_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function lw_feature_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'user_assessment_progress_report';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eck_user_assessment';
  $view->human_name = 'user assessment progress report';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'user assessment progress report';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'subject' => 'subject',
    'totaltime' => 'totaltime',
    'totalq' => 'totalq',
    'correcta' => 'correcta',
    'php' => 'php',
    'php_1' => 'php_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'subject' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'totaltime' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'totalq' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'correcta' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: User_assessment: subject */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'eck_user_assessment';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  $handler->display->display_options['fields']['subject']['label'] = 'Subject';
  /* Field: User_assessment: totaltime */
  $handler->display->display_options['fields']['totaltime']['id'] = 'totaltime';
  $handler->display->display_options['fields']['totaltime']['table'] = 'eck_user_assessment';
  $handler->display->display_options['fields']['totaltime']['field'] = 'totaltime';
  $handler->display->display_options['fields']['totaltime']['exclude'] = TRUE;
  /* Field: User_assessment: totalq */
  $handler->display->display_options['fields']['totalq']['id'] = 'totalq';
  $handler->display->display_options['fields']['totalq']['table'] = 'eck_user_assessment';
  $handler->display->display_options['fields']['totalq']['field'] = 'totalq';
  $handler->display->display_options['fields']['totalq']['label'] = 'Total Question';
  /* Field: User_assessment: correcta */
  $handler->display->display_options['fields']['correcta']['id'] = 'correcta';
  $handler->display->display_options['fields']['correcta']['table'] = 'eck_user_assessment';
  $handler->display->display_options['fields']['correcta']['field'] = 'correcta';
  $handler->display->display_options['fields']['correcta']['exclude'] = TRUE;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Time spent';
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_value'] = 'echo elapsed_time($row->totaltime,6);

 $time = $row->totaltime;
   $a = array(\'decade\' => 315576000, \'year\' => 31557600, \'month\' => 2629800, \'week\' => 604800, \'day\' => 86400, \'hour\' => 3600, \'min\' => 60, \'sec\' => 1);
   $i = 0;
     foreach($a as $k => $v) {
       $$k = floor($time/$v);
       if ($$k) $i++;
       $time = $i >= 6 ? 0 : $time - $$k * $v;
       $s = $$k > 1 ? \'s\' : \'\';
       $$k = $$k ? $$k.\' \'.$k.$s.\' \' : \'\';
       @$result .= $$k;
     }
return $result;';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['label'] = 'Accuracy';
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_value'] = 'if ($row->totalq >0)
  $per = ($row->correcta*100)/$row->totalq;
else
  $per = 0;
return round($per, 2) . "%";';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  /* Sort criterion: User_assessment: Id */
  $handler->display->display_options['sorts']['id']['id'] = 'id';
  $handler->display->display_options['sorts']['id']['table'] = 'eck_user_assessment';
  $handler->display->display_options['sorts']['id']['field'] = 'id';
  $handler->display->display_options['sorts']['id']['order'] = 'DESC';
  /* Contextual filter: User_assessment: Author */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'eck_user_assessment';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: User_assessment: user_assessment type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_user_assessment';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'user' => 'user',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'user-assessment-progress-report';
  $export['user_assessment_progress_report'] = $view;

  return $export;
}
