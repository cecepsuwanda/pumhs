<?php
  require_once dirname(dirname(__FILE__)).'/shared.php'; 
class dt_opt_log
{
   var $tb;
   var $numrows;  
  
   function __construct(){
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
	
   function logout($lg_time,$id)
   {       
	   $this->tb->updateRecord(array('lg_time'=>$lg_time,'user'=>$id,'out_time'=>date("Y-m-d H:i:s")));
	   return 1;
   }

   function login($lg_time,$id)
   {       
	   $this->tb->insertRecord(array('lg_time'=>$lg_time,'user'=>$id));
	   return 1;
   }
	
	
}
?>