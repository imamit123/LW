<?php
/**
 * @file
 * parent_entity.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function parent_entity_eck_entity_type_info() {
$items = array(
       'parent_assignment' => array(
  'name' => 'parent_assignment',
  'label' => 'parent assignment',
  'properties' => array(
    'uid' => array(
      'label' => 'Author',
      'type' => 'integer',
      'behavior' => 'author',
    ),
    'subject' => array(
      'label' => 'topic',
      'type' => 'text',
      'behavior' => '',
    ),
    'topic' => array(
      'label' => 'topic',
      'type' => 'text',
      'behavior' => '',
    ),
    'easy' => array(
      'label' => 'easy',
      'type' => 'integer',
      'behavior' => '',
    ),
    'very_easy' => array(
      'label' => 'very_easy',
      'type' => 'integer',
      'behavior' => '',
    ),
    'difficult' => array(
      'label' => 'difficult',
      'type' => 'integer',
      'behavior' => '',
    ),
    'very_difficult' => array(
      'label' => 'very_difficult',
      'type' => 'integer',
      'behavior' => '',
    ),
    'total' => array(
      'label' => 'total',
      'type' => 'integer',
      'behavior' => '',
    ),
    'topic_id' => array(
      'label' => 'topic_id',
      'type' => 'text',
      'behavior' => '',
    ),
    'nids' => array(
      'label' => 'nids',
      'type' => 'text',
      'behavior' => '',
    ),
    'due_date' => array(
      'label' => 'due_date',
      'type' => 'text',
      'behavior' => '',
    ),
    'created_date' => array(
      'label' => 'created_date',
      'type' => 'text',
      'behavior' => '',
    ),
  ),
),
  );
  return $items;
}
