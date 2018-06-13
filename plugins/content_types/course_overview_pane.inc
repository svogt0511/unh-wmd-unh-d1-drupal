<?php

/**
 * @file
 * Define a ctools plugin to D1 course section displays (right rail section list).
 *
 * See constants .inc file. 
 */

/**
 * Define Plugin.
 */
 $plugin = array(
  'title'           => t('Course Node Overview Pane'),
  'single'          => FALSE,
  'description'     => t('Course overview from from D1 API.'),
  'category'        => array('UNH DestinyOne'),
  'all contexts'    => TRUE,
  'edit form'       => 'course_overview_pane_content_type_edit_form',
  'render callback' => 'course_overview_pane_content_type_render',
);
 
/**
 * Title callback for admin page.
 */
function course_overview_pane_admin_title($subtype, $conf, $context = NULL) {
  return t('Course Node Overview Pane');
}
 
/**
 * Callback to provide administrative info (the preview in panels when building a panel).
 */
function course_overview_pane_admin_info($subtype, $conf, $context = NULL) {
  $block = new stdClass();
  $block->title = t('Course Overview Pane');
  $config = array();
  if ($conf['override_title'] == TRUE) {
    $title_value = '<b>' . $conf['override_title_text'] . '</b>';
  }
  else {
    $title_value = t('Not Set');
  }
  $config[] = t('Title') . ': ' . $title_value;
  $block->content = theme_item_list(array( 'items' => $config, 'title' => NULL, 'type' => 'ul', 'attributes' => array() ));
  return $block;
}
 
/**
 * Edit callback for the content type.
 */
function course_overview_pane_content_type_edit_form($form, &$form_state) {

  $conf = $form_state['conf'];
  
  return $form;
}
 
/**
 * Submit callback for settings form.
 */
function course_overview_pane_content_type_edit_form_submit($form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}
 
/**
 * Run-time rendering course sections pane (right-rail list of section blocks).
 */
 function course_overview_pane_content_type_render($subtype, $conf, $panel_args) {
  
  $block = NULL;
  $node = menu_get_object();
  $config = $conf;
  
  if ($node->type == 'course') {
    $wrapper = entity_metadata_wrapper('node', $node);
    $course_code = $wrapper->field_course_code->value();
    $course = NULL;
    $course_overview = '';
    
    // Get course data.
    if (!empty($course_code)) {
      $information_level = 'full';
      $program_area = unh_d1_drupal_settings_program_area();
      
      $course = unh_d1_client_searchCourse_courseCode($course_code, array($program_area), $information_level);
      $course_overview = '<div class="course-overview">' . unh_d1_client_getcourseOverview($course) . '</div>';
      
      $course_certificates_block = '';
      
        // Make sure we have a D1 course.
      if (!empty($node->field_course_code)) {

        // Now get the markup for certificates.
        if (!empty($node->field_certificate)) {

          $items = field_get_items('node', $node, 'field_certificate');
          $course_certificates = '';
          foreach ($items as $item) {
            $fc = field_collection_field_get_entity($item);
            if (!empty($fc)) {
              $url = $fc->field_certificate_page['und'][0]['url'];
              $title = $fc->field_certificate_title['und'][0]['value'];

              $course_certificates .= '
  <div class="certificate">
    <a href="' . $url . '"><i class="fa ' . UNH_D1_DRUPAL_CERTIFICATE_ICON . '"></i>' . $title . '</a>
  </div>';
            }
          }
          
          if (!empty($course_certificates)) {
            $course_certificates_block = '
<div class="certificates-block">
' . $course_certificates . '
</div>';
          }
        }
      }
      
     $course_overview .= $course_certificates_block;

      // Render the content with either theme() or by building a render array.
      $block = new stdClass();
      $block->content = array(
        // Render with theme() - example.
        // $args = array('course_nid' => '160', 'sections' => '20') + $panel_args;
        // '#markup' => theme('unh_d1_drupal__course_sections_pane', $args)
        // '#markup' => d1pdt_courseView_infoPane($panel_args[0])

        // Render with a render array - example.
        '#theme' => 'unh_d1_drupal__d1__course_overview_pane',
        '#course_nid' => $node->nid,
        '#course' => $course,
        '#course_overview' => $course_overview,
        // '#sections' => $sections,
        '#config' => $config,
        /*
        '#attached' => array(
          'js'=> array(
            drupal_get_path('module', 'unh_d1_drupal') . '/js/unh_d1_drupal.sections_pane.js',
            array(
              'data' => array(
                'courseId' => $courseId,
                'sectionIds' => $sectionIds,
                'section_status' => 'SECTION IS AVAILABLE'
              ),
              'type' => 'setting',
            ),
          )
        )
        */
      );
    } else {
      $course_overview = '<div class="course-overview">' . $wrapper->field_overview->value()['safe_value'] . '</div>';
      
      // Render the content with either theme() or by building a render array.
      $block = new stdClass();
      $block->content = array(
        // Render with theme() - example.
        // $args = array('course_nid' => '160', 'sections' => '20') + $panel_args;
        // '#markup' => theme('unh_d1_drupal__course_sections_pane', $args)
        // '#markup' => d1pdt_courseView_infoPane($panel_args[0])

        // Render with a render array - example.
        '#theme' => 'unh_d1_drupal__non_d1__course_overview_pane',
        '#course_nid' => $node->nid,
        '#course' => $course,
        '#course_overview' => $course_overview,
        // '#sections' => $sections,
        '#config' => $config,
        /*
        '#attached' => array(
          'js'=> array(
            drupal_get_path('module', 'unh_d1_drupal') . '/js/unh_d1_drupal.sections_pane.js',
            array(
              'data' => array(
                'courseId' => $courseId,
                'sectionIds' => $sectionIds,
                'section_status' => 'SECTION IS AVAILABLE'
              ),
              'type' => 'setting',
            ),
          )
        )
        */
      );
      
      
    }
  }
  
  return $block;
}