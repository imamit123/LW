<?php
/**
 * @file
 * all_menus_with_link.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function all_menus_with_link_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: management.
  $menus['management'] = array(
    'menu_name' => 'management',
    'title' => 'Management',
    'description' => 'The <em>Management</em> menu contains links for administrative tasks.',
  );
  // Exported menu: menu-about-menu.
  $menus['menu-about-menu'] = array(
    'menu_name' => 'menu-about-menu',
    'title' => 'About_menu',
    'description' => '',
  );
  // Exported menu: menu-features-menu.
  $menus['menu-features-menu'] = array(
    'menu_name' => 'menu-features-menu',
    'title' => 'features_menu',
    'description' => '',
  );
  // Exported menu: menu-menu-for-not-logged-in-user.
  $menus['menu-menu-for-not-logged-in-user'] = array(
    'menu_name' => 'menu-menu-for-not-logged-in-user',
    'title' => 'Menu for not logged in users',
    'description' => '',
  );
  // Exported menu: menu-product-menu.
  $menus['menu-product-menu'] = array(
    'menu_name' => 'menu-product-menu',
    'title' => 'Product_menu',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About_menu');
  t('Management');
  t('Menu for not logged in users');
  t('Product_menu');
  t('The <em>Management</em> menu contains links for administrative tasks.');
  t('features_menu');


  return $menus;
}
