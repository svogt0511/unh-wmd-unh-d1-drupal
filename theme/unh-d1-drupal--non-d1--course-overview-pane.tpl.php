<?php 
if (!empty($course_overview)) {
  $node = node_load($course_nid);
  $view = field_view_field('node', $node, 'field_course_image', array('label' => 'hidden'));
  $course_image_block = render($view);
  // $course_overview = unh_d1_client_getcourseOverview($course);
  $course_title_block = views_embed_view('course', 'panel_pane_9', $node->nid);
?> 
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div class='course-overview-pane'>
    <div class="course-overview-pane-content">
      <?=$course_image_block?>
      <?=$course_title_block?>
      <?=$course_overview?>
    </div>
  </div> <!-- course-overview-pane -->
</div> <!--<?=$classes?>-->
<?php
}
?>