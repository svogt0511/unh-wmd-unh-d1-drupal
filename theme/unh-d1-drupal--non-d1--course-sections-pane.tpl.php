<div>RENDERING NON-D1 SECTIONS</div>
<?php
if (!empty($course_nid)) {
  $node = node_load($course_nid);
  if (!empty($node)) {
?> 
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div id="ajax-target-801725"></div>
  <div id="ajax-target-801751"></div>  
  <div id="ajax-target"></div>

  <div class='course-info_pane'>

<?php
  // @todo: get the $always_display_first_open flag from the panel settings
    //$i = 0;
    //$first = TRUE; 
    //$disp_open = $config['disp_open'];
    $output = '';
    $course_is_available =_unh_d1_drupal_non_d1_course_is_available($node);
    if ($course_is_available) {
      $course_title = _unh_d1_drupal_non_d1_course_title($node);
    ?>
    <div class='card course-info-pane'>
      <div class='card-header' role='tab' id='courseHeader'>
        <h5 class='mb-0'>
          <a href='$current_url'>
            <?=$course_title?>
          </a>
        </h5>
      </div>  <!-- card-header -->
    </div> <!-- course-info-pane -->

<?php
    } else {
        // Commented this out - shows nothing on 'section unavailable'.
        $output .= "<!-- <div class='section-unavailable'>$sectionTitle (UNAVAILABLE $sectionSemester)</div> -->";
    }
  
?>
    <?=$output?>
  </div> <!--course-info_pane--> 
</div> <!--<?=$classes?>-->
<?php
  }
}
?>

