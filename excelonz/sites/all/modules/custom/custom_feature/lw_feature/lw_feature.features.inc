<?php
/**
 * @file
 * lw_feature.features.inc
 */

/**
 * Implements hook_views_api().
 */
function lw_feature_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_eck_bundle_info().
 */
function lw_feature_eck_bundle_info() {
  $items = array(
  'user_assessment_user' => array(
  'machine_name' => 'user_assessment_user',
  'entity_type' => 'user_assessment',
  'name' => 'user',
  'label' => 'user',
),
  'user_info_user' => array(
  'machine_name' => 'user_info_user',
  'entity_type' => 'user_info',
  'name' => 'user',
  'label' => 'user',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function lw_feature_eck_entity_type_info() {
$items = array(
       'user_assessment' => array(
  'name' => 'user_assessment',
  'label' => 'user_assessment',
  'properties' => array(
    'subject' => array(
      'label' => 'subject',
      'type' => 'text',
      'behavior' => '',
    ),
    'totalq' => array(
      'label' => 'totalq',
      'type' => 'integer',
      'behavior' => '',
    ),
    'correcta' => array(
      'label' => 'correcta',
      'type' => 'integer',
      'behavior' => '',
    ),
    'totaltime' => array(
      'label' => 'totaltime',
      'type' => 'integer',
      'behavior' => '',
    ),
    'uid' => array(
      'label' => 'Author',
      'type' => 'integer',
      'behavior' => 'author',
    ),
  ),
),
       'user_info' => array(
  'name' => 'user_info',
  'label' => 'user_info',
  'properties' => array(
    'subject' => array(
      'label' => 'subject',
      'type' => 'text',
      'behavior' => '',
    ),
    'level' => array(
      'label' => 'level',
      'type' => 'integer',
      'behavior' => '',
    ),
    'uid' => array(
      'label' => 'Author',
      'type' => 'integer',
      'behavior' => 'author',
    ),
  ),
),
  );
  return $items;
}

/**
 * Implements hook_node_info().
 */
function lw_feature_node_info() {
  $items = array(
    'mcq' => array(
      'name' => t('MCQ'),
      'base' => 'node_content',
      'description' => t('This content type stores Multiple Choice Questions '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
