<?php
/**
 * @file
 * go_live.features.inc
 */

/**
 * Implements hook_views_api().
 */
function go_live_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_eck_entity_type_info().
 */
function go_live_eck_entity_type_info() {
$items = array(
       'notifications' => array(
  'name' => 'notifications',
  'label' => 'Notifications',
  'properties' => array(
    'title' => array(
      'label' => 'Title',
      'type' => 'text',
      'behavior' => '',
    ),
    'uid' => array(
      'label' => 'Author',
      'type' => 'integer',
      'behavior' => 'author',
    ),
    'nid_interger' => array(
      'label' => 'nid',
      'type' => 'integer',
      'behavior' => '',
    ),
    'uid_integer' => array(
      'label' => 'uid',
      'type' => 'integer',
      'behavior' => '',
    ),
    'entity_type' => array(
      'label' => 'Type',
      'type' => 'text',
      'behavior' => '',
    ),
  ),
),
  );
  return $items;
}

/**
 * Implements hook_node_info().
 */
function go_live_node_info() {
  $items = array(
    'go_live' => array(
      'name' => t('Go Live'),
      'base' => 'node_content',
      'description' => t('Content type for go live session'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
