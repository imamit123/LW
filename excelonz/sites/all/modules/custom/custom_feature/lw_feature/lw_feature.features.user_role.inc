<?php
/**
 * @file
 * lw_feature.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function lw_feature_user_default_roles() {
  $roles = array();

  // Exported role: Content Owner.
  $roles['Content Owner'] = array(
    'name' => 'Content Owner',
    'weight' => '3',
  );

  return $roles;
}
