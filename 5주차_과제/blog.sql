-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema DB1
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema DB1
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `DB1` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci ;
USE `DB1` ;

-- -----------------------------------------------------
-- Table `DB1`.`Category`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `DB1`.`Category` (
  `id_category` INT NOT NULL AUTO_INCREMENT,
  `cate_name` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id_category`),
  UNIQUE INDEX `id_category_UNIQUE` (`id_category` ASC) VISIBLE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `DB1`.`Main`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `DB1`.`Main` (
  `id_main` INT NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id_main`),
  UNIQUE INDEX `id_main_UNIQUE` (`id_main` ASC) VISIBLE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `DB1`.`User`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `DB1`.`User` (
  `uid` INT NOT NULL AUTO_INCREMENT,
  `user_name` VARCHAR(45) NOT NULL,
  `user_id` VARCHAR(45) NOT NULL,
  `user_pwd` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`uid`),
  UNIQUE INDEX `uid_UNIQUE` (`uid` ASC) VISIBLE,
  UNIQUE INDEX `user_id_UNIQUE` (`user_id` ASC) VISIBLE)
ENGINE = InnoDB
AUTO_INCREMENT = 3
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `DB1`.`Content`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `DB1`.`Content` (
  `id_cont` INT NOT NULL AUTO_INCREMENT,
  `cont_num` INT NOT NULL,
  `Main_id_main` INT NOT NULL,
  `User_uid` INT NOT NULL,
  PRIMARY KEY (`id_cont`),
  UNIQUE INDEX `id_cont_UNIQUE` (`id_cont` ASC) VISIBLE,
  INDEX `fk_Content_Main1_idx` (`Main_id_main` ASC) VISIBLE,
  INDEX `fk_Content_User1_idx` (`User_uid` ASC) VISIBLE,
  CONSTRAINT `fk_Content_Main1`
    FOREIGN KEY (`Main_id_main`)
    REFERENCES `DB1`.`Main` (`id_main`),
  CONSTRAINT `fk_Content_User1`
    FOREIGN KEY (`User_uid`)
    REFERENCES `DB1`.`User` (`uid`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `DB1`.`Category_has_Content`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `DB1`.`Category_has_Content` (
  `Category_id_category` INT NOT NULL,
  `Content_id_cont` INT NOT NULL,
  PRIMARY KEY (`Category_id_category`, `Content_id_cont`),
  INDEX `fk_Category_has_Content_Content1_idx` (`Content_id_cont` ASC) VISIBLE,
  INDEX `fk_Category_has_Content_Category1_idx` (`Category_id_category` ASC) VISIBLE,
  CONSTRAINT `fk_Category_has_Content_Category1`
    FOREIGN KEY (`Category_id_category`)
    REFERENCES `DB1`.`Category` (`id_category`),
  CONSTRAINT `fk_Category_has_Content_Content1`
    FOREIGN KEY (`Content_id_cont`)
    REFERENCES `DB1`.`Content` (`id_cont`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `DB1`.`Comment`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `DB1`.`Comment` (
  `id_comment` INT NOT NULL AUTO_INCREMENT,
  `comment_num` INT NOT NULL DEFAULT '0',
  `Content_id_cont` INT NOT NULL,
  `User_uid` INT NOT NULL,
  PRIMARY KEY (`id_comment`),
  UNIQUE INDEX `id_comment_UNIQUE` (`id_comment` ASC) VISIBLE,
  INDEX `fk_Comment_Content1_idx` (`Content_id_cont` ASC) VISIBLE,
  INDEX `fk_Comment_User1_idx` (`User_uid` ASC) VISIBLE,
  CONSTRAINT `fk_Comment_Content1`
    FOREIGN KEY (`Content_id_cont`)
    REFERENCES `DB1`.`Content` (`id_cont`),
  CONSTRAINT `fk_Comment_User1`
    FOREIGN KEY (`User_uid`)
    REFERENCES `DB1`.`User` (`uid`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
