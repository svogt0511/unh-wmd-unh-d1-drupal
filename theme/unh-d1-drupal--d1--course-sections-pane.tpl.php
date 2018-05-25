<?php
if (!empty($sections)) {
  // sort the sections
  if ($config['section_sort']['sort']) {
    $sections = unh_d1_drupal_sort_rr_sections($sections, $config['section_sort']['options'], $config['section_sort']['direction']);
  }

  $section_class = (!empty($config['section_status_cached']) ? 'cached' : 'noncached');
  $classes = (!empty($classes) ? $classes . ' ' . $section_class : $section_class);
?>
<div id="ajax-target"></div> 
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div class='sections_pane'>
    <div id='sectionAccordion' role='tablist' aria-multiselectable='true' class='sectionAccordion_class'>
  
<?php
  // @todo: get the $always_display_first_open flag from the panel settings
  $i = 0;
  $first = TRUE; 
  $disp_open = $config['disp_open'];
  $output = '';
  foreach ($sections as $section) {
    $i++;
    // Should we display the first section box open or closed?
    $disp_open = ($first && $disp_open);
    
    if (unh_d1_client_sectionIsAvailable($section) ||
        unh_d1_client_sectionIsFutureOffering($section) ||
        unh_d1_client_sectionIsWaitlisted($section) ||
        unh_d1_client_sectionIsEnrollmentClosed($section) ||
        unh_d1_client_sectionIsFull($section)) {
      
      $output .= theme('unh_d1_drupal__d1__course_section', 
        array('course_nid' => $course_nid,
          'course' => $course,
          'section' => $section,
          'config' => $config,
          'disp_idx' => $i,
          'disp_open' => $disp_open)
      );

      $disp_open = FALSE;
      $first = FALSE;
    } else {
      // Commented this out - shows nothing on 'section unavailable'.
      $sectionTitle = unh_d1_client_getsectionTitle($section);
      $sectionSemester = unh_d1_client_getsectionSemester($section);
      $output .= "<!-- <div class='section-unavailable'>$sectionTitle (UNAVAILABLE $sectionSemester)</div> -->";
    }
  }
  
  print($output);
?>

    </div> <!--sectionAccordion-->
  </div> <!--sections_pane-->
</div> <!--<?=$classes?>-->

<?php
}
?>

