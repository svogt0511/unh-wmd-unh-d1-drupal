(function($) {
  Drupal.behaviors.unh_d1_drupal = {
    attach: function (context, settings) {
      // console.log('section status is: ' + JSON.stringify(settings));
      unh_d1_drupal_ajax_load(settings.courseId, settings.sectionIds, settings.section_status)
    }
  };
console.log('got here already! 222');
})(jQuery);

console.log('got here already! 111');

function unh_d1_drupal_ajax_load(courseId, sectionIds, section_status) {
  
  console.log('courseId = ' + courseId);
  console.log('sectionIds = ' + JSON.stringify(sectionIds));
  console.log('section_status = ' + section_status);
  
  sectionIds.forEach((sectionId) => {
    jQuery("#ajax-target").load("/unh_d1_drupal/ajax/get_section_status/" + courseId + '/' + sectionId);
  });
  
}
