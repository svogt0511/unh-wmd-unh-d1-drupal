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
  'title'           => t('Course Node Sections Pane'),
  'single'          => FALSE,
  'description'     => t('List of sections and their information from D1 API.'),
  'category'        => array('UNH DestinyOne'),
  'all contexts'    => TRUE,
  'edit form'       => 'course_sections_pane_content_type_edit_form',
  'render callback' => 'course_sections_pane_content_type_render',
);
 
/**
 * Title callback for admin page.
 */
function course_sections_pane_admin_title($subtype, $conf, $context = NULL) {
  return t('Course Node Sections Pane');
}
 
/**
 * Callback to provide administrative info (the preview in panels when building a panel).
 */
function course_sections_pane_admin_info($subtype, $conf, $context = NULL) {
  $block = new stdClass();
  $block->title = t('Course Sections Pane');
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
function course_sections_pane_content_type_edit_form($form, &$form_state) {

  $conf = $form_state['conf'];
  
  $form['section_sort'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Section Sort Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,  
  );
   
  $form['section_sort']['sort'] = array(
    '#title' => t('Sort Sections'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['section_sort']['sort']), 
  );
  
  $form['section_sort']['options'] = array(
    '#type' => 'radios',
    '#title' => t('Sort Options'),
    '#options' => array(
      t('Sort by Start Date then by Section Title'),
      t('Sort by Section Title'),
    ),
    '#default_value' => (($form_state['op'] == 'add') ? 0 : $conf['section_sort']['options']), 
  );  
  
  $form['section_sort']['direction'] = array(
    '#type' => 'radios',
    '#title' => t('Sort Direction'),
    '#options' => array(
      t('Ascending'),
      t('Descending'),
    ),
    '#default_value' => (($form_state['op'] == 'add') ? 0 : $conf['section_sort']['direction']), 
  );

  // the drupal checkboxes form field definition
  $form['body_section_fields'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Section Body Settings'),
    '#collapsible' => FALSE,
    '#collapsed' => false,  
  );

  // the drupal checkboxes form field definition
  $form['body_section_fields']['section_dates'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Section Dates'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,  
  );

  $form['body_section_fields']['section_dates']['show'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Section Dates'),
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['section_dates']['show']), 
  );
  
  $form['body_section_fields']['section_dates']['options'] = array(
    '#type' => 'radios',
    '#title' => t('Date Options'),
    '#options' => array(
      t('Start Date Only'),
      t('Start and End Dates'),
    ),
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['section_dates']['options']),
  );
  
  $form['body_section_fields']['section_times'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Section Times'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,  
  );
   
  $form['body_section_fields']['section_times']['show'] = array(
    '#title' => t('Show Section Times'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['section_times']['show']) , 
  );
  
  $form['body_section_fields']['section_times']['options'] = array(
    '#type' => 'radios',
    '#title' => t('Time Options'),
    '#options' => array(
      t('Start Time Only'),
      t('Start and End Times'),
    ),
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['section_times']['options']) , 
  );
  
  $form['body_section_fields']['section_tuition'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Section Tuition'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,  
  );

  $form['body_section_fields']['section_tuition']['show'] = array(
    '#title' => t('Show Section Tuition'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['section_tuition']['show']) , 
  );
  
  $form['body_section_fields']['section_tuition']['options_label'] = array(
    '#markup' => '<div class="options-label">Tuition Options</div>'
  );

  $form['body_section_fields']['section_tuition']['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Tuition Label'),
    '#default_value' => (($form_state['op'] == 'add') ? "Cost:" : $conf['body_section_fields']['section_tuition']['label']) , 
  );

  $form['body_section_fields']['section_tuition']['published_code'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Published Cost Code'),
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['section_tuition']['published_code']) , 
  );
  
  $form['body_section_fields']['action_button'] = array(
    '#title' => t('Show Action Button'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['action_button']) , 
  ); 
 
  $form['body_section_fields']['section_locations'] = array(
    '#title' => t('Show Section Locations'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['section_locations']), 
  );
    
  $form['body_section_fields']['section_instructors'] = array(
    '#title' => t('Show Section Instructors'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['section_instructors']) , 
  );

  $form['body_section_fields']['section_contact_hours'] = array(
    '#title' => t('Show Section Contact Hours'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['section_contact_hours']) , 
  );

  $form['body_section_fields']['section_discounts'] = array(
    '#title' => t('Show Section Discounts'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['section_discounts']) , 
  );
  
  $form['body_section_fields']['section_notes'] = array(
    '#title' => t('Show Section Notes'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['section_notes']) , 
  );
  
  $form['body_section_fields']['section_ceus'] = array(
    '#title' => t('Show Section CEUs'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['section_ceus']) , 
  );
  
  $form['body_section_fields']['section_course_code'] = array(
    '#title' => t('Show Course Code'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['section_course_code']) , 
  );

  $form['body_section_fields']['section_number'] = array(
    '#title' => t('Show Section Number'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['body_section_fields']['section_number']) , 
  );
  
  $form['disp_open'] = array(
    '#title' => t('Display First Section Expanded'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['disp_open']), 
  ); 

  $form['section_status_cached'] = array(
    '#title' => t('Use Cached Section Status'),
    '#type' => 'checkbox',
    '#return_value' => 1, 
    '#default_value' => (($form_state['op'] == 'add') ? 1 : $conf['section_status_cached']), 
  );   

  return $form;
}
 
/**
 * Submit callback for settings form.
 */
function course_sections_pane_content_type_edit_form_submit($form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}
 
/**
 * Run-time rendering course sections pane (right-rail list of section blocks).
 */
 function course_sections_pane_content_type_render($subtype, $conf, $panel_args) {
 
  global $base_url;
  global $base_path;
  
  $block = NULL;
  $node = menu_get_object();
  $wrapper = entity_metadata_wrapper('node', $node);
  $course_code = $wrapper->field_course_code->value();
  $course_title = $wrapper->title->value();
  $course = NULL;
  $sections = array();
  $config = $conf;
  $courseId = 0;
  $sectionIds = array();
  $program_area = unh_d1_drupal_settings_program_area();

  if ($node->type == 'course') {
    // If course is available, display sections.
    if ((!empty($course_code) && unh_d1_client_courseIsAvailable_courseCode($course_code, array($program_area))) || (empty($course_code) && unh_d1_drupal_non_d1_course_is_available($node))) {
      // D1 Course Sections
      if (!empty($course_code)) {
          $information_level = 'full';
      
          $course = unh_d1_client_searchCourse_courseCode($course_code, array($program_area));
      
          if (!empty($course)) {
            $sections = unh_d1_client_searchCourseSections($course_code, array($program_area), $information_level);
        
            $courseId = unh_d1_client_getcourseObjectId($course);
            $sectionIds = unh_d1_client_getSectionArrayObjectIds($sections);
          }

        // Render the content with either theme() or by building a render array.
        $block = new stdClass();
        $block->content = array(
          // Render with theme() - example.
          // $args = array('course_nid' => '160', 'sections' => '20') + $panel_args;
          // '#markup' => theme('unh_d1_drupal__course_sections_pane', $args)
          // '#markup' => d1pdt_courseView_infoPane($panel_args[0])

          // Render with a render array - example.
          '#theme' => 'unh_d1_drupal__d1__course_sections_pane',
          '#course_nid' => $node->nid,
          '#course' => $course,
          '#sections' => $sections,
          '#config' => $config,
          '#attached' => array(
            'js'=> array(
              drupal_get_path('module', 'unh_d1_drupal') . '/js/unh_d1_drupal.sections_pane.js',
              array(
                'data' => array(
                  'nid' => $node->nid,
                  'programArea' => $program_area,
                  'courseCode' => $course_code,
                  'conf' => $conf,
                  'base_url' => $base_url
                ),
                'type' => 'setting',
              ),
            )
          )
        );
      }
      // Non-D1 Course Sections - only 1 'section' for a non-d1 course
      else {
        // Render the content with either theme() or by building a render array.
        $block = new stdClass();
        $block->content = array(
          // Render with theme() - example.
          // $args = array('course_nid' => '160', 'sections' => '20') + $panel_args;
          // '#markup' => theme('unh_d1_drupal__course_sections_pane', $args)
          // '#markup' => d1pdt_courseView_infoPane($panel_args[0])

          // Render with a render array - example.
          '#theme' => 'unh_d1_drupal__non_d1__course_sections_pane',
          '#course_nid' => $node->nid,
          '#course' => NULL,
          '#sections' => array(),
          '#config' => $config,
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
        );
      }

    // If course is unavailable, display 'request more info'.
    } else {
      $message = "<b>This course is currently unavailable.</b>";
      $output = '';

      // Get the 'request more information' (associated forms and files - goes in the right
      // side rail).  This form is optional.
      $form_nid = (!empty($node->field_more_info_webform) ? $node->field_more_info_webform['und'][0]['target_id'] : NULL);

      if (!empty($form_nid)) {
        $form_node = node_load($form_nid);
        $form_node_header_text = $form_node->title;
        $form_node_body_text = $message;
        if (!empty($form_node->field_body)) {
          $form_node_body_text .= '<br>' . $form_node->field_body['und'][0]['value'];
        }

        // if we have components in the webform whose ids are either 'course_title'
        // or 'course_code' assign them appropriate values from the $courseProfile.
        // This could be done better. (To do: - find a better implementation?).
        $key1 = unh_d1_drupal_array_search('form_key', 'course_title', $form_node->webform['components']);
        if (empty($key1)) {
          $key1 = unh_d1_drupal_array_search('form_key', 'course_name', $form_node->webform['components']);
        }
        $key2 = unh_d1_drupal_array_search('form_key', 'course_code', $form_node->webform['components']);
        if ($key1 != NULL) {
          $form_node->webform['components'][$key1]['value'] = $course_title;
        }
        if ($key2 != NULL) {
          $form_node->webform['components'][$key2]['value'] = $course_code;
        }
        //$form =  drupal_get_form('webform_client_form_' . $form_id, $form_node, array());
        $form =  drupal_get_form('webform_client_form_' . $form_nid, $form_node, array());
        $rendered_form = '
<div class="side-form-block">
  <div class="side-form-header">' . $form_node_header_text . '</div>' . '
  <div class="side-form-body">' . $form_node_body_text . '</div>' . '
  <div class="side-form">' . drupal_render($form) . '</div>
</div>';

        $output .= $rendered_form;
      } else {

      $output .= '
<div class="card course-unavailable">
  <div class = "card-header">
    ' . $message . '
  </div>
</div>
  ';
      }


      $block = new stdClass();
      $block->content = array(
        // Render with theme() - example.
        // $args = array('course_nid' => '160', 'sections' => '20') + $panel_args;
        // '#markup' => theme('unh_d1_drupal__course_sections_pane', $args)
        // '#markup' => d1pdt_courseView_infoPane($panel_args[0])

        // Render with a render array - example.
        '#markup' => $output
      ); 
 /////////////   
    }
  }
  
  return $block;
}