<?php
require_once 'default_table.class.inc';
class tb_opt_log extends Default_Table
{
    // additional class variables go here
    function __construct()
    {
        $this->tablename       = 'opt_log';
        
		$this->fieldlist       = array('id','lg_time','out_time','user','net_id','browser','os','tg');
        
		$this->sql_orderby         = '';
		
		$this->fieldlist['lg_time'] = array('pkey' => 'y');
		$this->fieldlist['user'] = array('pkey' => 'y');
		        
				
    } // end class constructor

} // end class
?>