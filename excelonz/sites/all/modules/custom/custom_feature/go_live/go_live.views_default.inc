<?php
/**
 * @file
 * go_live.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function go_live_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'golive_upcoming__session';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Golive_upcoming _session';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Golive_upcoming _session';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: user status (field_user_status) */
  $handler->display->display_options['relationships']['field_user_status_value']['id'] = 'field_user_status_value';
  $handler->display->display_options['relationships']['field_user_status_value']['table'] = 'field_data_field_user_status';
  $handler->display->display_options['relationships']['field_user_status_value']['field'] = 'field_user_status_value';
  $handler->display->display_options['relationships']['field_user_status_value']['required'] = TRUE;
  $handler->display->display_options['relationships']['field_user_status_value']['delta'] = '-1';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'go_live' => 'go_live',
  );

  /* Display: Go Live Future Session */
  $handler = $view->new_display('block', 'Go Live Future Session', 'block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Go Live Future Session';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Friend List (field_friend_list) */
  $handler->display->display_options['arguments']['field_friend_list_uid']['id'] = 'field_friend_list_uid';
  $handler->display->display_options['arguments']['field_friend_list_uid']['table'] = 'field_data_field_friend_list';
  $handler->display->display_options['arguments']['field_friend_list_uid']['field'] = 'field_friend_list_uid';
  $handler->display->display_options['arguments']['field_friend_list_uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_friend_list_uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['field_friend_list_uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_friend_list_uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_friend_list_uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'go_live' => 'go_live',
  );
  /* Filter criterion: Broken/missing handler */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  /* Filter criterion: Field collection item: request status (field_request_status) */
  $handler->display->display_options['filters']['field_request_status_value']['id'] = 'field_request_status_value';
  $handler->display->display_options['filters']['field_request_status_value']['table'] = 'field_data_field_request_status';
  $handler->display->display_options['filters']['field_request_status_value']['field'] = 'field_request_status_value';
  $handler->display->display_options['filters']['field_request_status_value']['relationship'] = 'field_user_status_value';
  $handler->display->display_options['filters']['field_request_status_value']['value'] = array(
    'Approved' => 'Approved',
  );

  /* Display: Go Live Past Session */
  $handler = $view->new_display('block', 'Go Live Past Session', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Golive Past Session';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Friend List (field_friend_list) */
  $handler->display->display_options['arguments']['field_friend_list_uid']['id'] = 'field_friend_list_uid';
  $handler->display->display_options['arguments']['field_friend_list_uid']['table'] = 'field_data_field_friend_list';
  $handler->display->display_options['arguments']['field_friend_list_uid']['field'] = 'field_friend_list_uid';
  $handler->display->display_options['arguments']['field_friend_list_uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_friend_list_uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['field_friend_list_uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_friend_list_uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_friend_list_uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'go_live' => 'go_live',
  );
  /* Filter criterion: Broken/missing handler */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '<';
  /* Filter criterion: Field collection item: request status (field_request_status) */
  $handler->display->display_options['filters']['field_request_status_value']['id'] = 'field_request_status_value';
  $handler->display->display_options['filters']['field_request_status_value']['table'] = 'field_data_field_request_status';
  $handler->display->display_options['filters']['field_request_status_value']['field'] = 'field_request_status_value';
  $handler->display->display_options['filters']['field_request_status_value']['relationship'] = 'field_user_status_value';
  $handler->display->display_options['filters']['field_request_status_value']['value'] = array(
    'Approved' => 'Approved',
  );
  $export['golive_upcoming__session'] = $view;

  return $export;
}
