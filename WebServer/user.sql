CREATE TABLE IF NOT EXISTS `user`(
	   `user_id` INT UNSIGNED AUTO_INCREMENT,
	   `password` VARCHAR(100) NOT NULL,
	   `salt` VARCHAR(40) NOT NULL,
	   `age` INT UNSIGNED,
	   PRIMARY KEY ( `user_id` )
	)ENGINE=InnoDB DEFAULT CHARSET=utf8;