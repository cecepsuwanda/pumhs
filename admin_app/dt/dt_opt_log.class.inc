<?php
 
 
 $server = $_SERVER['DOCUMENT_ROOT'];
 $base_path = $server. '/admin_app/';
 if(!is_dir($base_path)){
   if($server=="/home/uni10000/public_html/pumhs") {
        $base_path = $server . '/admin_app/';		
	} 
    else{
	  $base_path = $server . '/admin_app/';	 
	}  
 }
 
 include_once $base_path.'db/tb_opt_log.class.inc';
 

class dt_opt_log
{
   var $tb;
   var $numrows;  
  
   function dt_opt_log(){
     $this->tb = new tb_opt_log;
	 
   }
  
	function getData($where)
    {	  
	  
	  $this->tb->sql_from = "opt_log INNER JOIN tmst_operator ON opt_log.user=tmst_operator.id_opt";
	  
	  $this->tb->sql_orderby = "lg_time desc";
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	
	
	
}
?>