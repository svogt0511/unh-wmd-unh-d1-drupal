<div class="<?php print $classes; ddl($variables, '$variables - GOT HERE!!'); ?>"<?php print $attributes; ?>>
<h1>AWESOME!!!! GOT HERE!!! YEA!! YEA!! YEA!! YEA!!</h1>
<?php 
  ddl("111111111111");
  ddl($course_nid, '$course_nid');
  ddl($course, '$course');
  ddl($sections, '$sections');
  ddl($body_section_fields, '$body_section_fields');
  ddl($variables, '$variables');
  ddl("222222222222");
?>
  
</div>

<div class='sections_pane'>
  <div id='sectionAccordion' role='tablist' aria-multiselectable='true' class='sectionAccordion_class'>
  
<?php
  // @todo: get the $always_display_first_open flag from the panel settings
  $always_display_first_closed = TRUE;
  $i = 0;
  $first = TRUE; 
  $output = '';
  foreach ($sections as $section) {
    $i++;

    // Should we display the first section box open or closed?
    $disp_open = ($first && !$always_display_first_closed);
    
    
    if (unh_d1_client_sectionIsAvailable($section) ||
        unh_d1_client_sectionIsFutureOffering($section) ||
        unh_d1_client_sectionIsWaitlisted($section) ||
        unh_d1_client_sectionIsEnrollmentClosed($section) ||
        unh_d1_client_sectionIsFull($section)) {
        
      $output .= theme('unh_d1_drupal__course_section', 
        array('course_nid' => $course_nid,
          'course' => $course,
          'section' => $section,
          'config' => $body_section_fields,
          'section_num' => $i,
          'disp_open' => $disp_open)
      );

      if ($disp_open) {
        $first = FALSE;
      }
    } else {
      // Commented this out - shows nothing on 'section unavailable'.
      $output .= "<!-- <div class='section-unavailable'>$sectionTitle (UNAVAILABLE $sectionSemester)</div> -->";
    }
  }
  
  print($output);
?>

  </div> <!--sectionAccordion-->
</div> <!--sections_pane-->

