<?php
require_once 'default_table.class.inc';
class tb_admin_log extends Default_Table
{
    // additional class variables go here
    function tb_admin_log ()
    {
        $this->tablename       = 'admin_log';
        
		$this->fieldlist       = array('id','lg_time','out_time','user','net_id','browser','os','tg');
        
		$this->sql_orderby         = '';
		
		$this->fieldlist['lg_time'] = array('pkey' => 'y');
		$this->fieldlist['user'] = array('pkey' => 'y');
		        
				
    } // end class constructor

} // end class
?>