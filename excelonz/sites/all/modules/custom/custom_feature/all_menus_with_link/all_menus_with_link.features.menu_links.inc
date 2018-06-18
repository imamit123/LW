<?php
/**
 * @file
 * all_menus_with_link.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function all_menus_with_link_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_featuresmenu:admin/structure/menu/manage/menu-features-menu
  $menu_links['management_featuresmenu:admin/structure/menu/manage/menu-features-menu'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/menu/manage/menu-features-menu',
    'router_path' => 'admin/structure/menu/manage/%',
    'link_title' => 'features_menu',
    'options' => array(
      'identifier' => 'management_featuresmenu:admin/structure/menu/manage/menu-features-menu',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_menus:admin/structure/menu',
  );
  // Exported menu link: management_productmenu:admin/structure/menu/manage/menu-product-menu
  $menu_links['management_productmenu:admin/structure/menu/manage/menu-product-menu'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/menu/manage/menu-product-menu',
    'router_path' => 'admin/structure/menu/manage/%',
    'link_title' => 'Product_menu',
    'options' => array(
      'identifier' => 'management_productmenu:admin/structure/menu/manage/menu-product-menu',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_menus:admin/structure/menu',
  );
  // Exported menu link: menu-about-menu_about-us:node/149881
  $menu_links['menu-about-menu_about-us:node/149881'] = array(
    'menu_name' => 'menu-about-menu',
    'link_path' => 'node/149881',
    'router_path' => 'node/%',
    'link_title' => 'About us',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-about-menu_about-us:node/149881',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-about-menu_contact-us:node/12207
  $menu_links['menu-about-menu_contact-us:node/12207'] = array(
    'menu_name' => 'menu-about-menu',
    'link_path' => 'node/12207',
    'router_path' => 'node/%',
    'link_title' => 'Contact us',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-about-menu_contact-us:node/12207',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-about-menu_home:<front>
  $menu_links['menu-about-menu_home:<front>'] = array(
    'menu_name' => 'menu-about-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-about-menu_home:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-about-menu_how-to-use-excelonz:node/228674
  $menu_links['menu-about-menu_how-to-use-excelonz:node/228674'] = array(
    'menu_name' => 'menu-about-menu',
    'link_path' => 'node/228674',
    'router_path' => 'node/%',
    'link_title' => 'How to use Excelonz',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-about-menu_how-to-use-excelonz:node/228674',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-about-menu_terms--conditions:node/12258
  $menu_links['menu-about-menu_terms--conditions:node/12258'] = array(
    'menu_name' => 'menu-about-menu',
    'link_path' => 'node/12258',
    'router_path' => 'node/%',
    'link_title' => 'Terms & Conditions',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-about-menu_terms--conditions:node/12258',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: menu-about-menu_why-excelonz:why-excelonz
  $menu_links['menu-about-menu_why-excelonz:why-excelonz'] = array(
    'menu_name' => 'menu-about-menu',
    'link_path' => 'why-excelonz',
    'router_path' => 'why-excelonz',
    'link_title' => 'Why Excelonz',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-about-menu_why-excelonz:why-excelonz',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-features-menu_activate:<front>
  $menu_links['menu-features-menu_activate:<front>'] = array(
    'menu_name' => 'menu-features-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Activate',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-features-menu_activate:<front>',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-features-menu_member-login:user/login
  $menu_links['menu-features-menu_member-login:user/login'] = array(
    'menu_name' => 'menu-features-menu',
    'link_path' => 'user/login',
    'router_path' => 'user/login',
    'link_title' => 'Member Login',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-features-menu_member-login:user/login',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-features-menu_pricing:node/9380
  $menu_links['menu-features-menu_pricing:node/9380'] = array(
    'menu_name' => 'menu-features-menu',
    'link_path' => 'node/9380',
    'router_path' => 'node/%',
    'link_title' => 'Pricing',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-features-menu_pricing:node/9380',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-features-menu_sign-up:node/9380
  $menu_links['menu-features-menu_sign-up:node/9380'] = array(
    'menu_name' => 'menu-features-menu',
    'link_path' => 'node/9380',
    'router_path' => 'node/%',
    'link_title' => 'Sign Up',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-features-menu_sign-up:node/9380',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-menu-for-not-logged-in-user_blog:http://blog.excelonz.com/
  $menu_links['menu-menu-for-not-logged-in-user_blog:http://blog.excelonz.com/'] = array(
    'menu_name' => 'menu-menu-for-not-logged-in-user',
    'link_path' => 'http://blog.excelonz.com/',
    'router_path' => '',
    'link_title' => 'Blog',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-menu-for-not-logged-in-user_blog:http://blog.excelonz.com/',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-menu-for-not-logged-in-user_contact:node/12207
  $menu_links['menu-menu-for-not-logged-in-user_contact:node/12207'] = array(
    'menu_name' => 'menu-menu-for-not-logged-in-user',
    'link_path' => 'node/12207',
    'router_path' => 'node/%',
    'link_title' => 'Contact',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-menu-for-not-logged-in-user_contact:node/12207',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: menu-menu-for-not-logged-in-user_faqs:node/9382
  $menu_links['menu-menu-for-not-logged-in-user_faqs:node/9382'] = array(
    'menu_name' => 'menu-menu-for-not-logged-in-user',
    'link_path' => 'node/9382',
    'router_path' => 'node/%',
    'link_title' => 'FAQs',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-menu-for-not-logged-in-user_faqs:node/9382',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-menu-for-not-logged-in-user_home:<front>
  $menu_links['menu-menu-for-not-logged-in-user_home:<front>'] = array(
    'menu_name' => 'menu-menu-for-not-logged-in-user',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-menu-for-not-logged-in-user_home:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-menu-for-not-logged-in-user_pricing:node/9380
  $menu_links['menu-menu-for-not-logged-in-user_pricing:node/9380'] = array(
    'menu_name' => 'menu-menu-for-not-logged-in-user',
    'link_path' => 'node/9380',
    'router_path' => 'node/%',
    'link_title' => 'Pricing',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-menu-for-not-logged-in-user_pricing:node/9380',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-menu-for-not-logged-in-user_why-excelonz:why-excelonz
  $menu_links['menu-menu-for-not-logged-in-user_why-excelonz:why-excelonz'] = array(
    'menu_name' => 'menu-menu-for-not-logged-in-user',
    'link_path' => 'why-excelonz',
    'router_path' => 'why-excelonz',
    'link_title' => 'Why Excelonz',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-menu-for-not-logged-in-user_why-excelonz:why-excelonz',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About us');
  t('Activate');
  t('Blog');
  t('Contact');
  t('Contact us');
  t('FAQs');
  t('Home');
  t('How to use Excelonz');
  t('Member Login');
  t('Pricing');
  t('Product_menu');
  t('Sign Up');
  t('Terms & Conditions');
  t('Why Excelonz');
  t('features_menu');


  return $menu_links;
}
