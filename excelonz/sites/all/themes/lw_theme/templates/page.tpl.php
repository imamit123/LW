<?php
/**
 * @file
 * Adaptivetheme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * Adaptivetheme supplied variables:
 * - $site_logo: Themed logo - linked to front with alt attribute.
 * - $site_name: Site name linked to the homepage.
 * - $site_name_unlinked: Site name without any link.
 * - $hide_site_name: Toggles the visibility of the site name.
 * - $visibility: Holds the class .element-invisible or is empty.
 * - $primary_navigation: Themed Main menu.
 * - $secondary_navigation: Themed Secondary/user menu.
 * - $primary_local_tasks: Split local tasks - primary.
 * - $secondary_local_tasks: Split local tasks - secondary.
 * - $tag: Prints the wrapper element for the main content.
 * - $is_mobile: Bool, requires the Browscap module to return TRUE for mobile
 *   devices. Use to test for a mobile context.
 * - *_attributes: attributes for various site elements, usually holds id, class
 *   or role attributes.
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Core Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * Adaptivetheme Regions:
 * - $page['leaderboard']: full width at the very top of the page
 * - $page['menu_bar']: menu blocks placed here will be styled horizontal
 * - $page['secondary_content']: full width just above the main columns
 * - $page['content_aside']: like a main content bottom region
 * - $page['tertiary_content']: full width just above the footer
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see adaptivetheme_preprocess_page()
 * @see adaptivetheme_process_page()
 */
?>

<?php //@todo: remove this js add?>
<?php drupal_add_js( drupal_get_path('module', 'golive') . '/nodejs.golive.js');?>
<div id="page" class="container <?php print $classes; ?>">
<?php
	global $user;
	global $base_url;
	$current_user = user_load($user->uid);
	//echo '<pre>';print_r($current_user->field_child_id);die();
	$name = $current_user->field_first_name['und'][0]['value'];
?>
  <!-- region: Leaderboard -->
  <?php print render($page['leaderboard']); ?>

  <header<?php print $header_attributes; ?>>
    <div class="header-container">
    <?php if ($site_logo || $site_name || $site_slogan): ?>
      <!-- start: Branding -->
      <div<?php print $branding_attributes; ?>>

        <?php if ($site_logo): ?>
          <div id="logo">
            <?php
            	/* Page redirect, clicking on site logo based on roles */
            	if($user->roles[5] == 'Parent'){
            		print '
            		<a class="active" title="Home page" href="'. $base_url.'/dashboard/parent">
            		<img alt="Learning World" src="'. $base_url.'/'.path_to_theme().'/logo.png" typeof="foaf:Image" class="site-logo image-style-none">
            		</a>';
            	}

            	if($user->roles[6] == 'student'){
            		print '
            		<a class="active" title="Home page" href="'. $base_url.'/dashboard/student/">
            		<img alt="Learning World" src="'. $base_url.'/'.path_to_theme().'/logo.png" typeof="foaf:Image" class="site-logo image-style-none">
            		</a>';
            	}
            	if($user->roles[7] == 'Teacher'){
            		print '
            		<a class="active" title="Home page" href="'. $base_url.'/dashboard/teacher">
            		<img alt="Learning World" src="'. $base_url.'/'.path_to_theme().'/logo.png" typeof="foaf:Image" class="site-logo image-style-none">
            		</a>';
            	}
            	if($user->roles[1] == 'anonymous user' || $user->roles[3] == 'administrator'  ){
            		print '
            		<a class="active" title="Home page" href="/">
            			<img alt="Learning World" src="'. $base_url.'/'.path_to_theme().'/logo.png" typeof="foaf:Image" class="site-logo image-style-none">
            		</a>';
				}
            ?>
          </div>
        <?php endif; ?>

        <?php if ($site_name || $site_slogan): ?>
          <!-- start: Site name and Slogan hgroup -->
          <hgroup<?php print $hgroup_attributes; ?>>

            <?php if ($site_name): ?>
              <h1<?php print $site_name_attributes; ?>><?php //print $site_name; ?></h1>
            <?php endif; ?>

            <?php if ($site_slogan): ?>
              <h2<?php print $site_slogan_attributes; ?>><?php print $site_slogan; ?></h2>
            <?php endif; ?>

          </hgroup><!-- /end #name-and-slogan -->
        <?php endif; ?>

      </div><!-- /end #branding -->
    <?php endif; ?>

    <!-- region: Header -->
    <?php print render($page['header']); ?>
	<div class="clearfix"></div> <!-- Added for removing float effect -->
	</div>
  </header>
  <div class="container_block">
	<div class="inner_block">
	  <!-- Navigation elements -->
	  <?php print render($page['menu_bar']); ?>
	  <?php //if ($primary_navigation): //print $primary_navigation; endif; ?>
	  <?php if ($secondary_navigation): print $secondary_navigation; endif; ?>

	  <!-- Breadcrumbs -->
	  <?php if ($breadcrumb): print $breadcrumb; endif; ?>

	  <!-- Messages and Help -->
	  <?php print $messages; ?>
	  <?php print render($page['help']); ?>

	  <!-- region: Secondary Content -->
	  <?php print render($page['secondary_content']); ?>

	  <div id="columns" class="columns clearfix">
		<div id="content-column" class="content-column" role="main">
		  <div class="content-inner">

			<!-- region: Highlighted -->
			<?php print render($page['highlighted']); ?>

			<<?php print $tag; ?> id="main-content">

			  <?php print render($title_prefix); // Does nothing by default in D7 core ?>

			  <?php if ($title || $primary_local_tasks || $secondary_local_tasks || $action_links = render($action_links)): ?>
				<header<?php print $content_header_attributes; ?>>

				  <?php if ($title): ?>

					<h1 id="page-title">
					  <?php

						if(($user->roles[5] == 'Parent') && arg(1) == $user->uid && arg(0) == 'user' && arg(2) != 'edit' ) {
							$ul = user_load($user->uid);
					  		if(count($ul->field_child_id) == 0){
							print 'Hi '.$name.", Please add your child's details.";
							}
							else{
								print 'Hi '.$name. ',' ;
							}
						}
						elseif ($user->roles[5] == 'Parent' && arg(1) != $user->uid && arg(0) == 'user' && arg(2) != 'edit') {
							$current_user = user_load(arg(1));
							$name = $current_user->field_first_name['und'][0]['value'] . " " . $current_user->field_last_name['und'][0]['value'];
							print $name . "'s Profile";
						}
						elseif(($user->roles[7] == 'Teacher') && arg(0) == 'user') {
							$current_user = user_load(arg(1));
							$last_name = $current_user->field_last_name['und'][0]['value'];
							print 'Hello '.$name.' '.$last_name;
						}
						elseif(($user->roles[7] == 'Teacher') && arg(1) == '11923') {
							$last_name = $current_user->field_last_name['und'][0]['value'];
							print 'Hello '.$name.' '.$last_name.', your dashboard';
						}
			            elseif ($user->roles[5] == 'Parent' && arg(1) != $user->uid && arg(0) == 'user' && arg(2) == 'edit') {
			              $current_user = user_load(arg(1));
			              $name1 = $current_user->field_first_name['und'][0]['value'] . " " . $current_user->field_last_name['und'][0]['value'];
			              print 'Hi '.$name.', Please update '. $name1 ."'s details.";
			            }
						elseif( arg(0) == 'user' && arg(2) === 'edit') {
							print 'Hi '.$name.', Please update your details.';
						}
						elseif( ($user->roles[6] == 'student') && arg(0) == 'user') {
							print 'Hi '.$name.',' ;
						}
						elseif(arg(0) == 'profile-second_parent' && arg(1) == $user->uid && arg(2) != 'edit' ) {
							print "Second Parent's Details" ;
						}
						elseif(arg(0) == 'profile-second_parent' && arg(1) == $user->uid && arg(2) == 'edit' ) {
							print "Edit Second Parent's Details" ;
						}
						else {
							print $title;
						}
					  ?>
					</h1>
				  <?php endif; ?>

				  <?php if ($primary_local_tasks || $secondary_local_tasks || $action_links): ?>
					<div id="tasks">

					  <?php if ($primary_local_tasks): ?>
						<ul class="tabs primary clearfix"><?php print render($primary_local_tasks); ?></ul>
					  <?php endif; ?>

					  <?php if ($secondary_local_tasks): ?>
						<ul class="tabs secondary clearfix"><?php print render($secondary_local_tasks); ?></ul>
					  <?php endif; ?>

					  <?php if ($action_links = render($action_links)): ?>
						<ul class="action-links clearfix"><?php print $action_links; ?></ul>
					  <?php endif; ?>

					</div>
				  <?php endif; ?>

				</header>
				<?php $sidebar_first = render($page['sidebar_first']); print $sidebar_first; ?>
			  <?php endif; ?>

			  <!-- region: Main Content -->
			  <?php if ($content = render($page['content'])): ?>
				<div id="content" class="region">
				  <?php print $content; ?>
				</div>
			  <?php endif; ?>

			  <!-- Feed icons (RSS, Atom icons etc -->
			  <?php print $feed_icons; ?>

			  <?php print render($title_suffix); // Prints page level contextual links ?>

			</<?php print $tag; ?>><!-- /end #main-content -->

			<!-- region: Content Aside -->
			<?php print render($page['content_aside']); ?>

		  </div><!-- /end .content-inner -->
		</div><!-- /end #content-column -->

		<!-- regions: Sidebar first and Sidebar second -->

		<?php $sidebar_second = render($page['sidebar_second']); print $sidebar_second; ?>

		  <!-- region: Footer -->
  <?php if ($page['footer']): ?>
    <footer<?php print $footer_attributes; ?>>
      <?php print render($page['footer']); ?>
    </footer>
  <?php endif; ?>

	  </div><!-- /end #columns -->
	  </div>
  </div>
  </div>
  <p id="back-top">
		<a href="#top"><span></span>Go to Top</a>
  </p>
  <div class="body-bottom-bg">test</div>
  <!-- region: Tertiary Content -->
  <?php print render($page['tertiary_content']); ?>



</div>
