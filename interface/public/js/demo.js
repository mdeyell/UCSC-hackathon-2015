// Function to motor direction
$(document).ready(function() {

  $("#1").click(function() {//manual
    $.get('/light/digital/7/0', function() {
      $.get('/light/digital/7/0');
    });

  });
/*
  $("#2").click(function() {//light off
    $.get('/light/digital/7/0', function() {
      $.get('/light/digital/13/0');
    });
  });
*/
  $("#3").click(function() {//automated
    $.get('/light/digital/7/1', function() {
      $.get('/light/digital/7/1');
    });
  });

  $("#4").click(function() {//manual
    $.get('/light/digital/6/0', function() {
      $.get('/light/digital/6/0');
     
    });
  });
/*
  $("#5").click(function() {//light off
    $.get('/light/digital/6/0', function() {
      $.get('/light/digital/12/0');
    });

  });
*/
  $("#6").click(function() {//automated
    $.get('/light/digital/6/1', function() {
      $.get('/light/digital/6/1');
    });
  });
    
  // Function to control room 1 intensity
  $("#intensity1").mouseup(function(){
    // Get speed
    speed = $("#intensity1").val(); 
    
    // Send command
    $.get("/light/analog/4/" + speed);  

  });
  
    // Function to control room 2 intensity
  $("#intensity2").mouseup(function(){
    // Get speed
    speed = $("#intensity2").val(); 
    
    // Send command
    $.get("/light/analog/5/" + speed);  

  });

});